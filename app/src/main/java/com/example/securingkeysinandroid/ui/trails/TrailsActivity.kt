package com.example.securingkeysinandroid.ui.trails

import android.content.pm.PackageManager
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.securingkeysinandroid.BuildConfig
import com.example.securingkeysinandroid.R
import com.example.securingkeysinandroid.utils.AESCrypt
import kotlinx.android.synthetic.main.activity_trails.*
import java.security.GeneralSecurityException


class TrailsActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_trails)
    }

    override fun onResume() {
        super.onResume()
        initViews()
    }

    fun initViews() {
        val password = "password"
        val message = "hello world"
        var encryptedMsg = ""
        try {
            encryptedMsg = AESCrypt.encrypt(password, message)
        } catch (e: GeneralSecurityException) {
            //handle error
        }

        textView.text = BuildConfig.BUILD_TYPE + ", $encryptedMsg"
        //textView2.text = getString(R.string.myra_api_key) + ", ${stringFromJNI()}"


        try {
            val applicationInfo = packageManager.getApplicationInfo(packageName, PackageManager.GET_META_DATA)
            if (applicationInfo.metaData == null) {
                applicationInfo.metaData = Bundle()
            }
            applicationInfo.metaData.putString("truecaller_partner_key", "Sv7uU766a029b78134248b44f42c26c2de3c7")
            textView2.text = applicationInfo.metaData.getString("truecaller_partner_key")
        } catch (e: PackageManager.NameNotFoundException) {
            e.printStackTrace()
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
