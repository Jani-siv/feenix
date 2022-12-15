package com.example.fenixapplication.db_models

import java.util.*

data class DeviceModel(
    var id: Int = getAutoId(),
    var deviceId: String = "",
    var devicePassword: String = ""
) {
    companion object {
        fun getAutoId(): Int {
            val random = Random()
            return random.nextInt(100)
        }
    }
}
