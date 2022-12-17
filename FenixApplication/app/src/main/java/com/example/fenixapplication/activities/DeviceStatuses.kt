package com.example.fenixapplication.activities

import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.fenixapplication.R
import com.example.fenixapplication.recyclerAdapters.RecyclerAdapterStatuses
import com.example.fenixapplication.db_models.SQLiteHelper

class DeviceStatuses : AppCompatActivity() {
    private lateinit var sqliteHelper: SQLiteHelper
    private lateinit var recyclerViewStatuses: RecyclerView
    private lateinit var deviceSelectedName: TextView
    private var adapter: RecyclerAdapterStatuses? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.fragment_devicestatuses)
        dataInitialize()
        sqliteHelper = SQLiteHelper(this)
        recyclerInitialize()
    }

    private fun recyclerInitialize() {
        recyclerViewStatuses.layoutManager = LinearLayoutManager(this)
        adapter = RecyclerAdapterStatuses()
        recyclerViewStatuses.adapter = adapter

        val stdListStatuses = sqliteHelper.getDeviceStatusHistory("")
        adapter?.addItems(stdListStatuses)
    }

    private fun dataInitialize() {
        deviceSelectedName = findViewById(R.id.device_name_statuses)
        recyclerViewStatuses = findViewById(R.id.recyclerViewStatuses)
    }
}
