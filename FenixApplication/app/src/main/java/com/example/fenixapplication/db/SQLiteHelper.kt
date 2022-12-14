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
        private const val TBL_STATUS = "tbl_status"
        private const val STATUS_ID = "status_id"
        private const val STATUS_TO_DEVICE = "status_to_device"
        private const val DATE = "status_date"
        private const val STATUS_MIN = "status_min"
        private const val STATUS_CURRENT = "status_current"
        private const val STATUS_MAX = "status_max"
    }

    override fun onCreate(db: SQLiteDatabase?) {
        val createTblDeviceStatus =
            ("CREATE TABLE "
                    + TBL_DEVICE + "("
                    + ID + " INTEGER PRIMARY KEY AUTOINCREMENT,"
                    + DEVICE_ID + " TEXT" + ")")
            ("CREATE TABLE "
                    + TBL_STATUS + "("
                    + STATUS_ID + " INTEGER PRIMARY KEY AUTOINCREMENT,"
                    + STATUS_TO_DEVICE + " INTEGER FOREIGN KEY REFERENCES tbl_device(id),"
                    + DATE + " DATETIME,"
                    + STATUS_MIN + " TEXT,"
                    + STATUS_CURRENT + " TEXT,"
                    + STATUS_MAX + " TEXT" + ")")
        db?.execSQL(createTblDeviceStatus)
    }

    override fun onUpgrade(db: SQLiteDatabase?, oldVersion: Int, newVersion: Int) {
        db!!.execSQL("DROP TABLE IF EXISTS $TBL_DEVICE")
        db!!.execSQL("DROP TABLE IF EXISTS $TBL_STATUS")
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

    fun insertStatus(std: StatusModel): Long {
        val db = this.writableDatabase

        val contentValues = ContentValues()
        contentValues.put(STATUS_ID, std.status_id)
        contentValues.put(STATUS_TO_DEVICE, std.status_to_device)
        contentValues.put(DATE, std.status_date)
        contentValues.put(STATUS_MIN, std.status_min)
        contentValues.put(STATUS_CURRENT, std.status_current)
        contentValues.put(STATUS_MAX, std.status_max)

        val success = db.insert(TBL_STATUS, null, contentValues)
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

    // TODO - function need be working when get connection
    @SuppressLint("Range")
    fun getDeviceStatusHistory(deviceID: Int): ArrayList<StatusModel> {
        val stdList: ArrayList<StatusModel> = ArrayList()
        val selectQuery = "SELECT status_date, status_min, status_current, status_max FROM $TBL_STATUS WHERE status_to_device = $deviceID"
        val db = this.readableDatabase
        val cursor: Cursor?

        try {
            cursor = db.rawQuery(selectQuery, null)
        } catch (e: Exception) {
            e.printStackTrace()
            db.execSQL(selectQuery)
            return ArrayList()
        }

        var statusId: Int
        var statusToDevice: String
        var statusDate: String
        var statusMin: String
        var statusCurrent: String
        var statusMax: String

        if(cursor.moveToFirst()) {
            do {
                statusId = cursor.getInt(cursor.getColumnIndex("status_id"))
                statusToDevice = cursor.getString(cursor.getColumnIndex("status_to_device"))
                statusDate = cursor.getString(cursor.getColumnIndex("status_date"))
                statusMin = cursor.getString(cursor.getColumnIndex("status_min"))
                statusCurrent = cursor.getString(cursor.getColumnIndex("status_current"))
                statusMax = cursor.getString(cursor.getColumnIndex("status_max"))
                val std = StatusModel(status_id = statusId, status_to_device = statusToDevice,
                    status_date = statusDate, status_min = statusMin, status_current = statusCurrent, status_max = statusMax)
                stdList.add(std)
            }
            while (cursor.moveToFirst())
        }
        return stdList
    }

    fun deleteDevice(id: Int): Int {
        val db = this.writableDatabase
        val contentValues = ContentValues()
        contentValues.put(ID, id)
        val success = db.delete(TBL_DEVICE, "id=$id", null)
        db.close()
        return success
    }
}
