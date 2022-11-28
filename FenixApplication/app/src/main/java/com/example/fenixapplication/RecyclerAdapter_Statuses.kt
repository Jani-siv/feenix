package com.example.fenixapplication

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import com.example.fenixapplication.db.DeviceModel

class RecyclerAdapter_Statuses : RecyclerView.Adapter<RecyclerAdapter.DeviceViewHolder>() {

    private var stdList: ArrayList<DeviceModel> = ArrayList()

    fun addItems( items : ArrayList<DeviceModel>) {
        this.stdList = items
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int) =
        RecyclerAdapter.DeviceViewHolder(
            LayoutInflater.from(parent.context).inflate(R.layout.card_statuses_layout, parent, false)
        )

    override fun onBindViewHolder(holder: RecyclerAdapter.DeviceViewHolder, position: Int) {
        val std = stdList[position]
        holder.bindView(std)
    }

    override fun getItemCount(): Int {
        return stdList.size
    }

}