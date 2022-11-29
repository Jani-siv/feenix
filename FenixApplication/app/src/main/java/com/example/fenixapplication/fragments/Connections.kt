package com.example.fenixapplication.fragments

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
import com.example.fenixapplication.RecyclerAdapter
import com.example.fenixapplication.db.DeviceModel
import com.example.fenixapplication.db.SQLiteHelper

class Connections : Fragment(R.layout.fragment_connections) {

    private lateinit var deviceIdEd: EditText
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
        recyclerInitialize()
        sqliteHelper = SQLiteHelper(context)

        btnAddConnection.setOnClickListener { addConnectionToDatabase() }
        btnRefresh.setOnClickListener { getDevicesFromDatabase() }

        adapter?.activateButtons(true)
        adapter?.setOnClickDeleteItem {
            deleteDevice(it.id)
        }
    }

    private fun addConnectionToDatabase() {
        val deviceId = deviceIdEd.text.toString()
        if (deviceId.isEmpty()) {
            Toast.makeText(context, "Enter required field", Toast.LENGTH_SHORT).show()
        }
        else {
            val std = DeviceModel(deviceId = deviceId)
            val status = sqliteHelper.insertDevice(std)
            if(status > -1) {
                Toast.makeText(context, "Device added", Toast.LENGTH_SHORT).show()
                deviceIdEd.setText("")
                deviceIdEd.requestFocus()
                val stdList = sqliteHelper.getAllDevices()
                adapter?.addItems(stdList)
            }
            else {
                Toast.makeText(context, "Device not added", Toast.LENGTH_SHORT).show()
            }
        }
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
    }

    private fun dataInitialize() {
        deviceIdEd = requireView().findViewById(R.id.device_idED)
        btnAddConnection = requireView().findViewById(R.id.btnAddConnection)
        btnRefresh = requireView().findViewById(R.id.btnRefresh)
        recyclerView = requireView().findViewById(R.id.recyclerView)
    }

}
