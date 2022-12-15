package com.example.fenixapplication.recyclerAdapters

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.fenixapplication.R
import com.example.fenixapplication.db_models.DeviceModel

class RecyclerAdapter : RecyclerView.Adapter<RecyclerAdapter.DeviceViewHolder>() {
    private var stdList: ArrayList<DeviceModel> = ArrayList()
    private var onClickDeleteItem: ((DeviceModel) -> Unit)? = null
    private var activate: Boolean = false

    class DeviceViewHolder(var view: View) : RecyclerView.ViewHolder(view) {
        private var deviceName = view.findViewById<TextView>(R.id.device_name)
        var deleteBtn: Button? = view.findViewById<Button>(R.id.btnDeleteDevice)
        fun bindView(std: DeviceModel) {
            deviceName.text = std.deviceId
        }
    }

    fun addItems( items : ArrayList<DeviceModel>) {
        this.stdList = items
        notifyDataSetChanged()
    }

    fun setOnClickDeleteItem(callback:(DeviceModel)->Unit) {
        this.onClickDeleteItem = callback
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int) = DeviceViewHolder(
        LayoutInflater.from(parent.context).inflate(R.layout.card_layout, parent, false)
    )

    override fun onBindViewHolder(holder: DeviceViewHolder, position: Int) {
        val std = stdList[position]
        holder.bindView(std)
        if(activate) {
            holder.deleteBtn?.visibility = View.VISIBLE;
            holder.deleteBtn?.setOnClickListener { onClickDeleteItem?.invoke(std)}
        } else {
            holder.deleteBtn?.visibility = View.INVISIBLE
        }
    }

    override fun getItemCount(): Int {
        return stdList.size
    }

    fun activateButtons(activate: Boolean) {
        this.activate = activate
        notifyDataSetChanged()
    }
}
