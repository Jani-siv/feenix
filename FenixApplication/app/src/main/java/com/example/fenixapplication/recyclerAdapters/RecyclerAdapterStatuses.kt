package com.example.fenixapplication.recyclerAdapters

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.fenixapplication.R
import com.example.fenixapplication.db_models.StatusModel

class RecyclerAdapterStatuses : RecyclerView.Adapter<RecyclerAdapterStatuses.StatusViewHolder>() {

    private var stdList: ArrayList<StatusModel> = ArrayList()

    fun addItems(items: ArrayList<StatusModel>) {
        this.stdList = items
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int) =
        StatusViewHolder(
            LayoutInflater.from(parent.context).inflate(R.layout.card_statuses_layout, parent, false)
        )

    override fun onBindViewHolder(holder: StatusViewHolder, position: Int) {
        val std = stdList[position]
        holder.bindView(std)
    }

    override fun getItemCount(): Int {
        return stdList.size
    }

    class StatusViewHolder(var view: View) : RecyclerView.ViewHolder(view) {
        private var statusDate = view.findViewById<TextView>(R.id.date)
        private var statusMin = view.findViewById<TextView>(R.id.min)
        private var statusNow = view.findViewById<TextView>(R.id.now)
        private var statusMax = view.findViewById<TextView>(R.id.max)

        fun bindView(std: StatusModel) {
            statusDate.text = std.status_date
            statusMin.text = std.status_min
            statusNow.text = std.status_current
            statusMax.text = std.status_max
        }
    }
}
