package com.example.fenixapplication

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class Home : Fragment(R.layout.fragment_home) {

    private lateinit var newRecyclerView: RecyclerView
    private lateinit var newArrayList: ArrayList<Devices>
    lateinit var deviceName : Array<String>
    lateinit var deviceStatus : Array<String>
    lateinit var deviceLastActivity : Array<String>

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? = inflater.inflate(R.layout.fragment_home, container, false)


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        deviceName = arrayOf("#1", "#2", "#3")
        deviceStatus = arrayOf("#1 S", "#2 S", "#3 S")
        deviceLastActivity = arrayOf("#1 L", "#2 L", "#3 L")

        newArrayList = arrayListOf<Devices>()
        getDeviceData()

    }

    private fun getDeviceData() {
        for(i in deviceName.indices) {
            val devices = Devices(deviceName[i], deviceStatus[i], deviceLastActivity[i])
            newArrayList.add(devices)
        }
        newRecyclerView.adapter = RecyclerAdapter(newArrayList)
    }

}