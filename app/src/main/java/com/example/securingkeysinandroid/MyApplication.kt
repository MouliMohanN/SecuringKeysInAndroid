package com.example.securingkeysinandroid

import android.app.Application


/**
 * Created by Mouli on 27-Jun-2019
 */
class MyApplication: Application() {
    override fun onCreate() {
        super.onCreate()
        /*try {
            val applicationInfo = packageManager.getApplicationInfo(packageName, PackageManager.GET_META_DATA)
            applicationInfo.metaData.putString("truecaller_partner_key", "Sv7uU766a029b78134248b44f42c26c2de3c7")
        } catch (e: PackageManager.NameNotFoundException) {
            e.printStackTrace()
        }*/

    }
}