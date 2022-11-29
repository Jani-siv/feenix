package com.example.fenixapplication

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.fenixapplication.db.StatusModel

class RecyclerAdapter_Statuses : RecyclerView.Adapter<RecyclerAdapter_Statuses.StatusViewHolder>() {

    private var stdList: ArrayList<StatusModel> = ArrayList()

    fun addItems( items : ArrayList<StatusModel>) {
        this.stdList = items
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int) =
        RecyclerAdapter_Statuses.StatusViewHolder(
            LayoutInflater.from(parent.context).inflate(R.layout.card_statuses_layout, parent, false)
        )

    override fun onBindViewHolder(holder: RecyclerAdapter_Statuses.StatusViewHolder, position: Int) {
        val std = stdList[position]
        holder.bindView(std)
    }

    override fun getItemCount(): Int {
        return stdList.size
    }

    class StatusViewHolder(var view: View) : RecyclerView.ViewHolder(view) {
        private var deviceId = view.findViewById<TextView>(R.id.device_name)
        fun bindView(std: StatusModel) {
            deviceId.text = std.status_to_device
        }
    }

}
