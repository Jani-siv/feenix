package com.example.fenixapplication.db_models

import android.annotation.SuppressLint
import android.content.ContentValues
import android.content.Context
import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import android.util.Log
import java.lang.Exception
import kotlin.collections.ArrayList

class SQLiteHelper(context: Context?) : SQLiteOpenHelper(context, DATABASE_NAME, null, DATABASE_VERSION) {

    companion object{
        private const val DATABASE_VERSION = 1
        private const val DATABASE_NAME = "devices.db"
        private const val TBL_DEVICE = "tbl_device"
        private const val ID = "id"
        private const val DEVICE_ID = "deviceId"
        private const val DEVICE_PASSWORD = "devicePassword"
        private const val TBL_STATUS = "tbl_status"
        private const val STATUS_ID = "status_id"
        private const val STATUS_TO_DEVICE = "status_to_device"
        private const val DATE = "status_date"
        private const val STATUS_MIN = "status_min"
        private const val STATUS_CURRENT = "status_current"
        private const val STATUS_MAX = "status_max"
    }

    override fun onCreate(db: SQLiteDatabase?) {
        val createTblDevice =
            ("CREATE TABLE "
                    + TBL_DEVICE + "("
                    + ID + " INTEGER PRIMARY KEY AUTOINCREMENT,"
                    + DEVICE_ID + " TEXT,"
                    + DEVICE_PASSWORD + " TEXT" + ")")

        val createTblStatus =
            ("CREATE TABLE "
                    + TBL_STATUS + "("
                    + STATUS_ID + " INTEGER PRIMARY KEY AUTOINCREMENT,"
                    + STATUS_TO_DEVICE + " INTEGER REFERENCES tbl_device(id),"
                    + DATE + " DATETIME,"
                    + STATUS_MIN + " TEXT,"
                    + STATUS_CURRENT + " TEXT,"
                    + STATUS_MAX + " TEXT" + ")")

        db?.execSQL(createTblDevice)
        db?.execSQL(createTblStatus)
    }

    override fun onUpgrade(db: SQLiteDatabase?, oldVersion: Int, newVersion: Int) {
        db!!.execSQL("DROP TABLE IF EXISTS $TBL_DEVICE")
        db!!.execSQL("DROP TABLE IF EXISTS $TBL_STATUS")
        onCreate(db)
    }

    fun insertDevice(stdD: DeviceModel): Long {
        val db = this.writableDatabase
        val contentValues = ContentValues()

        contentValues.put(ID, stdD.id)
        contentValues.put(DEVICE_ID, stdD.deviceId)
        contentValues.put(DEVICE_PASSWORD, stdD.devicePassword)

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
        contentValues.put(STATUS_CURRENT, std.status_current)

        val success = db.insert(TBL_STATUS, null, contentValues)
        db.close()
        return success
    }

    @SuppressLint("Range")
    fun getAllDevices(): ArrayList<DeviceModel> {
        val stdListDevices: ArrayList<DeviceModel> = ArrayList()
        val selectQuery = "SELECT * FROM $TBL_DEVICE"
        val db = this.readableDatabase
        val cursor: Cursor?

        var id: Int
        var deviceId: String

        try {
            cursor = db.rawQuery(selectQuery, null)
        } catch (e: Exception) {
            e.printStackTrace()
            db.execSQL(selectQuery)
            return ArrayList()
        }

        if(cursor.moveToFirst()) {
            do {
                id = cursor.getInt(cursor.getColumnIndex("id"))
                deviceId = cursor.getString(cursor.getColumnIndex("deviceId"))
                val std = DeviceModel(id = id, deviceId = deviceId)
                stdListDevices.add(std)
            } while (cursor.moveToNext())
        }
        return stdListDevices
    }

    @SuppressLint("Range")
    fun getDeviceStatusHistory(deviceID: String): ArrayList<StatusModel> {
        val stdListStatuses: ArrayList<StatusModel> = ArrayList()
        val selectQuery = "SELECT status_date, status_min, status_current, status_max FROM $TBL_STATUS WHERE status_to_device = $deviceID"
        val db = this.readableDatabase
        val cursor: Cursor?

        var statusToDevice: String
        var statusDate: String
        var statusMin: String
        var statusCurrent: String
        var statusMax: String

        try {
            cursor = db.rawQuery(selectQuery, null)
        } catch (e: Exception) {
            e.printStackTrace()
            db.execSQL(selectQuery)
            return ArrayList()
        }

        if(cursor.moveToFirst()) {
            do {
                statusToDevice = cursor.getString(cursor.getColumnIndex("status_to_device"))
                statusDate = cursor.getString(cursor.getColumnIndex("status_date"))
                statusMin = cursor.getString(cursor.getColumnIndex("status_min"))
                statusCurrent = cursor.getString(cursor.getColumnIndex("status_current"))
                statusMax = cursor.getString(cursor.getColumnIndex("status_max"))
                val std = StatusModel(
                    status_to_device = statusToDevice, status_date = statusDate,
                    status_min = statusMin, status_current = statusCurrent, status_max = statusMax)
                stdListStatuses.add(std)
                Log.d("Testing status", stdListStatuses.toString())
            }
            while (cursor.moveToFirst())
        }
        return stdListStatuses
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
