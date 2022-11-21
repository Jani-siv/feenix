package com.example.fenixapplication.db

import android.annotation.SuppressLint
import android.content.ContentValues
import android.content.Context
import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import java.lang.Exception

class SQLiteHelper(context: Context?) : SQLiteOpenHelper(context, DATABASE_NAME, null, DATABASE_VERSION) {

    companion object{
        private const val DATABASE_VERSION = 1
        private const val DATABASE_NAME = "devices.db"
        private const val TBL_DEVICE = "tbl_device"
        private const val ID = "id"
        private const val DEVICE_ID = "deviceId"
    }

    override fun onCreate(db: SQLiteDatabase?) {
        val createTblDevice =
            ("CREATE TABLE "
                    + TBL_DEVICE + "("
                    + ID + " INTEGER PRIMARY KEY AUTOINCREMENT,"
                    + DEVICE_ID + " TEXT" + ")")
        db?.execSQL(createTblDevice)
    }

    override fun onUpgrade(db: SQLiteDatabase?, oldVersion: Int, newVersion: Int) {
        db!!.execSQL("DROP TABLE IF EXISTS $TBL_DEVICE")
        onCreate(db)
    }

    fun insertDevice(std: DeviceModel): Long {
        val db = this.writableDatabase
        val contentValues = ContentValues()
        contentValues.put(ID, std.id)
        contentValues.put(DEVICE_ID, std.deviceId)
        val success = db.insert(TBL_DEVICE, null, contentValues)
        db.close()
        return success
    }

    @SuppressLint("Range")
    fun getAllDevices(): ArrayList<DeviceModel> {
        val stdList: ArrayList<DeviceModel> = ArrayList()
        val selectQuery = "SELECT * FROM $TBL_DEVICE"
        val db = this.readableDatabase
        val cursor: Cursor?

        try {
            cursor = db.rawQuery(selectQuery, null)
        } catch (e: Exception) {
            e.printStackTrace()
            db.execSQL(selectQuery)
            return ArrayList()
        }

        var id: Int
        var deviceId: String

        if(cursor.moveToFirst()) {
            do {
                id = cursor.getInt(cursor.getColumnIndex("id"))
                deviceId = cursor.getString(cursor.getColumnIndex("deviceId"))
                val std = DeviceModel(id = id, deviceId = deviceId)
                stdList.add(std)
            } while (cursor.moveToNext())
        }
        return stdList
    }

}
