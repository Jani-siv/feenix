package com.example.fenixapplication

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.fenixapplication.db.DeviceModel

class RecyclerAdapter : RecyclerView.Adapter<RecyclerAdapter.DeviceViewHolder>() {

    private var stdList: ArrayList<DeviceModel> = ArrayList()

    fun addItems( items : ArrayList<DeviceModel>) {
        this.stdList = items
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int) = DeviceViewHolder(
        LayoutInflater.from(parent.context).inflate(R.layout.card_layout, parent, false)
    )

    override fun onBindViewHolder(holder: DeviceViewHolder, position: Int) {
        val std = stdList[position]
        holder.bindView(std)
    }

    override fun getItemCount(): Int {
        return stdList.size
    }

    class DeviceViewHolder(var view: View) : RecyclerView.ViewHolder(view) {
        private var deviceId = view.findViewById<TextView>(R.id.device_name)
        fun bindView(std: DeviceModel) {
            deviceId.text = std.deviceId
        }
    }

}