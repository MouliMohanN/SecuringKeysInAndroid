package com.example.securingkeysinandroid

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_trails.*


class SecringKeysActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_trails)
    }

    override fun onResume() {
        super.onResume()
        initViews()
    }

    fun initViews() {

        var myApiKey = BuildConfig.my_api_key
        tv_decrypted_key.text = "Decrypted Key from gradle = ${decryptKey(myApiKey)}"
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun encryptKey(key: String): String
    external fun decryptKey(key: String): String

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
