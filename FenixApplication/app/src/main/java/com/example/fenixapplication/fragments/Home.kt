package com.example.fenixapplication.fragments

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.fenixapplication.R
import com.example.fenixapplication.RecyclerAdapter
import com.example.fenixapplication.db.SQLiteHelper

class Home : Fragment(R.layout.fragment_home) {

    private lateinit var sqliteHelper: SQLiteHelper
    private lateinit var recyclerView: RecyclerView
    private var adapter: RecyclerAdapter? = null

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? = inflater.inflate(R.layout.fragment_home, container, false)

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        dataInitialize()
        sqliteHelper = SQLiteHelper(context)
        recyclerInitialize()
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
    }

}
