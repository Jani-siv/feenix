package com.example.fenixapplication.fragments

import android.annotation.SuppressLint
import android.app.AlertDialog
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.fenixapplication.R
import com.example.fenixapplication.recyclerAdapters.RecyclerAdapter
import com.example.fenixapplication.db_models.DeviceModel
import com.example.fenixapplication.db_models.SQLiteHelper
import com.example.fenixapplication.db_models.StatusModel

class Connections : Fragment(R.layout.fragment_connections) {

    private lateinit var btnAddConnection: Button
    private lateinit var btnRefresh: Button
    private lateinit var sqliteHelper: SQLiteHelper
    private lateinit var recyclerView: RecyclerView
    private var adapter: RecyclerAdapter? = null

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? = inflater.inflate(R.layout.fragment_connections, container, false)

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        dataInitialize()
        sqliteHelper = SQLiteHelper(context)
        recyclerInitialize()
        btnAddConnection.setOnClickListener { addConnectionToDatabase() }
        btnRefresh.setOnClickListener { getDevicesFromDatabase() }
        adapter?.activateButtons(true)
        adapter?.setOnClickDeleteItem {
            deleteDevice(it.id)
        }
    }

    @SuppressLint("ResourceType")
    private fun addConnectionToDatabase() {
        val builder = AlertDialog.Builder(context)
        val inflater = layoutInflater
        val dialogLayout = inflater.inflate(R.layout.dialog_add_new_connection, null)
        val deviceId: EditText = dialogLayout.findViewById(R.id.deviceId)
        val devicePassword: EditText = dialogLayout.findViewById(R.id.devicePassword)

        builder.setView(dialogLayout)
        builder.setPositiveButton("Add") { dialog, _ ->
            val deviceIdChecking = deviceId.text.toString()
            val devicePasChecking = devicePassword.text.toString()
            val deviceCreatedId = DeviceModel.getAutoId()
            if (deviceIdChecking.isEmpty() || deviceIdChecking == "null" || deviceIdChecking == ""
                || devicePasChecking.isEmpty() || devicePasChecking == "null" || devicePasChecking == "") {
                Toast.makeText(context, "Enter required field", Toast.LENGTH_SHORT).show()
            } else {
                val stdD = DeviceModel(
                    id = deviceCreatedId,
                    deviceId = deviceIdChecking,
                    devicePassword = devicePasChecking
                )
                val stdS = StatusModel(
                    status_to_device = deviceCreatedId.toString(),
                    status_current = "Connecting"
                )
                val statusD = sqliteHelper.insertDevice(stdD)
                val statusS = sqliteHelper.insertStatus(stdS)

                if (statusD > -1) {
                    Toast.makeText(context, "Device added", Toast.LENGTH_SHORT).show()
                    val stdList = sqliteHelper.getAllDevices()
                    adapter?.addItems(stdList)
                } else {
                    Log.d("Testing device", statusD.toString())
                    Log.d("Testing status", statusS.toString())
                    Toast.makeText(context, "Device not added", Toast.LENGTH_SHORT).show()
                }
            }
        }
        builder.setNegativeButton("Cancel") { dialog, _ ->
            dialog.dismiss()
        }
        val alert = builder.create()
        alert.show()
    }

    private fun getDevicesFromDatabase() {
        val stdList = sqliteHelper.getAllDevices()
        adapter?.addItems(stdList)
    }

    private fun deleteDevice(id: Int) {
        val builder = AlertDialog.Builder(context)
        builder.setMessage("Delete this connection?")
        builder.setCancelable(true)
        builder.setPositiveButton("Yes") { dialog, _ ->
            sqliteHelper.deleteDevice(id)
            getDevicesFromDatabase()
            dialog.dismiss()
        }
        builder.setNegativeButton("No") { dialog, _ ->
            dialog.dismiss()
        }
        val alert = builder.create()
        alert.show()
    }

    private fun recyclerInitialize() {
        recyclerView.layoutManager = LinearLayoutManager(context)
        adapter = RecyclerAdapter()
        recyclerView.adapter = adapter
        val stdList = sqliteHelper.getAllDevices()
        adapter?.addItems(stdList)
    }

    private fun dataInitialize() {
        recyclerView = requireView().findViewById(R.id.recyclerView)
        btnAddConnection = requireView().findViewById(R.id.btnAddConnection)
        btnRefresh = requireView().findViewById(R.id.btnRefresh)
    }
}
