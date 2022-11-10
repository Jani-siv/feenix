package com.example.fenixapplication

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class Home : Fragment(R.layout.fragment_home) {

    private lateinit var recyclerView: RecyclerView
    private lateinit var adapter: RecyclerAdapter
    private lateinit var devicesArrayList: ArrayList<Devices>

    lateinit var deviceName : Array<String>
    lateinit var deviceStatus : Array<String>
    lateinit var deviceLastActivity : Array<String>

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? = inflater.inflate(R.layout.fragment_home, container, false)

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        dataInitialize()
        val layoutManager = LinearLayoutManager(context)
        recyclerView = view.findViewById(R.id.recyclerView)
        recyclerView.layoutManager = layoutManager
        recyclerView.setHasFixedSize(true)
        adapter = RecyclerAdapter(devicesArrayList)
        recyclerView.adapter = adapter
    }

    private fun dataInitialize() {
        devicesArrayList = arrayListOf<Devices>()
        deviceName = arrayOf("#1", "#2", "#3")
        deviceStatus = arrayOf("#1 S", "#2 S", "#3 S")
        deviceLastActivity = arrayOf("#1 L", "#2 L", "#3 L")

        for(i in deviceName.indices) {
            val devices = Devices(deviceName[i], deviceStatus[i], deviceLastActivity[i])
            devicesArrayList.add(devices)
        }
    }



}