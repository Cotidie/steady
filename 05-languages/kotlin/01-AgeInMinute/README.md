# Age In Minute
![aa](https://i.imgur.com/TBacqq8.png)  
 생년월일을 선택하면 나이를 분 단위로 표시해주는 앱


## 배운점
 * UI: Constraint Layout 연습, colors.xml, strings.xml 사용법
 * DatePickerDialog(context: Context, listener: DatePickerDialog.OnDateSetListener?, year: Int, month: Int, dayOfMonth: Int)
   * 참고링크: [Android Document](https://developer.android.com/reference/kotlin/android/app/DatePickerDialog)
   * 사용멤버: datePicker.maxDate, show()
 * Toast.makeText(this, msg, period).show()
   * 참고링크: [Android Document](https://developer.android.com/reference/android/widget/Toast?hl=en)
   * 비고: 화면 하단 짤막한 메시지. 디버그 용도로 사용함.

## 이슈
 * **Device Offline**: 실행 시 Device Offline으로 인하여 앱이 설치되지 않는 문제
    1. \[Tools\] > \[AVD Manager\]에서 장치 삭제 후 새로운 장치 생성
    2. \[Console\] > 'adb kill-server' 및 'adb start-server'
        - 단, 환경변수 PATH에 sdk\\platform-tools 경로가 지정되어 있어야 함. (Tools > SDK Manager에서 경로 확인 가능)
 * **findViewByID 문제**: Android Studio 4.1.1 이후부터 findViewByID 없이 ID로 객체에 접근할 수 없는 문제
    * 참고링크: [Youtube](https://www.youtube.com/watch?v=w5SYDRbGNXU)  
    ```kotlin
    // build.gradle(Module: ...)의 dependencies에 다음 2줄 추가
    apply plugin : "kotlin-android"
    apply plugin : "kotlin-android-extensions"
    ```
