package com.example.fenixapplication.db

import java.util.*

data class DeviceModel(
    var id: Int = getAutoId(),
    var deviceId: String = ""
) {
    companion object {
        fun getAutoId(): Int {
            val random = Random()
            return random.nextInt(100)
        }
    }
}