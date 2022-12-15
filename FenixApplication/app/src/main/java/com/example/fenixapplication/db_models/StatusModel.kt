package com.example.fenixapplication.db_models

import java.text.SimpleDateFormat
import java.util.*

data class StatusModel(
    var status_id: Int = getAutoId(),
    var status_to_device: String = "", // not auto-created id, reference to selected device
    var status_date: String = getCurrentTime(),
    var status_min: String = "",
    var status_current: String = "",
    var status_max: String = ""
) {
    companion object {
        fun getAutoId(): Int {
            val random = Random()
            return random.nextInt(100)
        }
        fun getCurrentTime(): String {
            val today = SimpleDateFormat("dd/M/yyyy hh:mm")
            return today.format(Date())
        }
    }
}
