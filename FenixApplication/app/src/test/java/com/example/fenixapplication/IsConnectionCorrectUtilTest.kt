package com.example.fenixapplication


import com.example.fenixapplication.utils.IsConnectionCorrectUtil
import com.google.common.truth.Truth.assertThat
import org.junit.Test

class IsConnectionCorrectUtilTest {


    @Test
    fun `empty id returns false`() {
        val result = IsConnectionCorrectUtil.validateConnectionInput(
            id = "",
            password = "1234"
        )
        assertThat(result).isFalse()
    }

    @Test
    fun `empty password returns false`() {
        val result = IsConnectionCorrectUtil.validateConnectionInput(
            id = "I02531",
            password = ""
        )
        assertThat(result).isFalse()
    }

    @Test
    fun `id and password is correct`() {
        val result = IsConnectionCorrectUtil.validateConnectionInput(
            id = "I02531",
            password = "1234"
        )
        assertThat(result).isTrue()
    }
}