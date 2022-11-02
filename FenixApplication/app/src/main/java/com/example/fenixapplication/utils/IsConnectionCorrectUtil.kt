package com.example.fenixapplication.utils

object IsConnectionCorrectUtil {


    fun validateConnectionInput(
        id: String,
        password: String
    ): Boolean {
        if(id.isEmpty() || password.isEmpty()) {
            return false
        }
        return true
    }



}