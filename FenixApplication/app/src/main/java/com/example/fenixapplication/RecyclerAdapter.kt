package com.example.fenixapplication

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class RecyclerAdapter(private val devicesList : ArrayList<Devices>) : RecyclerView.Adapter<RecyclerAdapter.MyViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MyViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.card_layout, parent, false)
        return MyViewHolder(itemView)
    }

    override fun onBindViewHolder(holder: MyViewHolder, position: Int) {
        val currentItem = devicesList[position]
        holder.deviceName.text = currentItem.deviceName
        holder.deviceStatus.text = currentItem.deviceStatus
        holder.deviceLastActivity.text = currentItem.deviceLastActivity
    }

    override fun getItemCount(): Int {
        return devicesList.size
    }


    class MyViewHolder(itemView : View) : RecyclerView.ViewHolder(itemView) {
        val deviceName : TextView = itemView.findViewById(R.id.device_name)
        val deviceStatus: TextView = itemView.findViewById(R.id.device_status)
        val deviceLastActivity: TextView = itemView.findViewById(R.id.device_lastactivity)
    }

}