# Bluetooth

## 사전 지식
- [권한 검사 및 요청](https://codechacha.com/ko/android-request-runtime-permissions/)

## 참고 문서
- [Android Developer](https://developer.android.com/guide/topics/connectivity/bluetooth)

## 주요 기능
- 블루투스 설정하기
- 블루투스 기기 스캔하기
- 블루투스 어댑터 쿼리
- 기기 간 데이터 주고받기
- 다수 기기에 대한 연결

## 기본
페어링 요청 -> 페어링 수락 -> 암호키 교환 -> (처리) -> 페어링 해제

## Bluetooth API
- [BluetoothAdapter](https://developer.android.com/reference/android/bluetooth/BluetoothAdapter): 블루투스 기기 간 통신을 위한 진입점. 페어링된 기기 목록, 데이터 교환 등을 관리한다.
- [BluetoothDevice](https://developer.android.com/reference/android/bluetooth/BluetoothDevice): 연결 가능한 원격 블루투스 기기를 표현하는 객체. BluetoothSocket을 통해 통신하거나 이름, 주소, bonding 상태 등으로 기기를 쿼리할 수 있다.
- [BluetoothSocket](https://developer.android.com/reference/android/bluetooth/BluetoothSocket): InputStream, OutputStream을 이용해 실제 통신을 수행하는 인터페이스.
- [BluetoothServerSocket](https://developer.android.com/reference/android/bluetooth/BluetoothServerSocket): 서버 역할을 하는 블루투스 기기의 소켓. 스마트폰 등으로부터 연결 요청을 수락하고 BluetoothSocket을 반환한다.

## Bluetooth Setup
### Permissions
Manifest에 블루투스 관련 권한을 명시해야 한다. Android 11 버전 이하에서는 다음 권한이 필요하다.
```xml
    // 블루투스 기기 탐색 및 페어링 요청 권한
    <uses-permission android:name="android.permission.BLUETOOTH" />
    // 블루투스 Discovery() 기능에 필요한 권한
    <uses-permission android:name="android.permission.BLUETOOTH_ADMIN" />
    // 블루투스 기기에 대한 위치 정보 접근 권한
    <uses-permission android:name="android.permission.ACCESS_FINE_LOCATION" />
    <uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" />
```
### Availability Check
기기에 BluetoothAdapter가 존재하는지, Bluetooth 기능이 켜져 있는지 검사한다.
```kotlin
private fun requestBluetooth() {
    val bluetoothManager: BluetoothManager = getSystemService(BluetoothManager::class.java)
    val bluetoothAdapter: BluetoothAdapter? = bluetoothManager.getAdapter()
    if (bluetoothAdapter == null) {
        // 이 기기는 블루투스를 지원하지 않음
        return
    }
    if (!bluetoothAdapter.isEnabled) {
        val launcher = registerForActivityResult(
            ActivityResultContracts.StartActivityForResult()
        ) {}

        val intent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
        launcher.launch(intent)
    }
}
```

## Companion Device Manager (Above API 26)
```xml
<uses-feature android:name="android.software.companion_device_setup"/>
```
안드로이드 API 28부터는 블루투스 기기 탐색(Bluetooth Discovery)를 Companion Device Manager로 제공한다. CDM은 편의상 블루투스, Wifi 기기 검색, 선택을 보조할 뿐 실제 연결이나 통신을 수행하지는 않는다.
* SDK 31부터는 BLUETOOTH_CONNECT 권한이 필요하다.

### **Bluetooth Discovery**
CDM은 탐색을 Associate로 표기한다. 참조관계는 Associate -> Request -> Filter이다.
- **Filter**: 스캔할 블루투스 기기에 대한 쿼리
- **Request**: 필터 및 스캔 옵션
- **Associate**: 페어링 요청
```kotlin
val deviceFilter = BluetoothDeviceFilter.Builder()
    // Device 이름 필터링
    .setNamePattern(Pattern.compile("My device"))
    // Device UUID 필터링
    .addServiceUuid(ParcelUuid(UUID(0x123abcL, -1L)), null)
    .build()

val pairingRequest = AssociationRequest.Builder()
    .addDeviceFilter(deviceFilter)
    // 1개만 찾고 탐색을 중지할지 선택
    .setSingleDevice(false)
    .build()
val deviceManager = context.getSystemService(Context.COMPANION_DEVICE_SERVICE) as CompanionDeviceManager
val pairingCallback = object: CompanionDeviceManager.Callback() {
    // 페어링 선택창 표시
    override fun onDeviceFound(chooserLauncher: IntentSender?) {
        // IntentSender Contract에 활용할 Request
        val request = IntentSenderRequest.Builder(chooserLauncher!!).build()
        // Activity Result API로 변경 필요
        // ActivityResult로 선택한 BluetoothDevice를 전달한다.
        startIntentSenderRequest(request)
    }

    override fun onFailure(error: CharSequence?) {
        Toast.makeText(context, error, Toast.LENGTH_LONG).show()
    }
}

deviceManager.associate(pairingRequest, pairingCallback, null)
```

## **Bluetooth Pairing**
위에서 찾은 BluetoothDevice를 페어링한다.

