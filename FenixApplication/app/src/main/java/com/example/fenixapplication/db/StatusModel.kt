package com.example.fenixapplication.db

import java.util.*

data class StatusModel(
    var status_id: Int = getAutoId(),
    var status_to_device: String = "",
    var status_date: String = "",
    var status_min: String = "",
    var status_current: String = "",
    var status_max: String = ""
) {
    companion object {
        fun getAutoId(): Int {
            val random = Random()
            return random.nextInt(100)
        }
    }
}
