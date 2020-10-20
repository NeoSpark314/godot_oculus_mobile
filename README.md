# Oculus Mobile Godot plugin for Oculus Quest Toolkit

For use with Godot 3.2 and the Godot Oculus Quest Toolkit

This branch is used to track the version of the Godot Oculus Mobile Plugin that is used in the Godot Oculus Quest Toolkit [https://github.com/NeoSpark314/godot_oculus_quest_toolkit](https://github.com/NeoSpark314/godot_oculus_quest_toolkit). It only supports the Oculus Quest. The main version of this plugin
can be found at https://github.com/GodotVR/godot_oculus_mobile.

A compiled plugin of this branch is available in the toolkit repository at https://github.com/NeoSpark314/godot_oculus_quest_toolkit/tree/master/addons/godot_ovrmobile


## Setup
After cloning this repository make sure to initialise the submodules with `git submodule init`.
When you've pulled a newer version make sure to run `git submodule update`.<br>
The project uses `cmake` as its primary build system, which you can configure by following the setup instructions
for the **Android SDK & NDK**.

### Android SDK & NDK
- Download and setup the [Android SDK](https://developer.android.com/studio/#command-tools).
  - If using Android Studio, download version **3.5** or higher.
  - If using the [command line tools](https://developer.android.com/studio/#command-tools), 
  download revision **26.1.1** or higher. 
  - To ensure you have the latest version, check [SDK Manager](https://developer.android.com/studio/intro/update.html#sdk-manager) for updates.  
- Add the Android SDK **cmake** binaries directory to the environment path. The directory can be found under 
`<android_sdk_location>/cmake/<cmake_version>/bin`.
  - Ensure that `cmake_version` is greater or equal to version `3.6.0`.   
- Download and setup the [latest version](https://developer.android.com/ndk/downloads) 
(version **r20** or higher) of the **Android NDK**.
- Set the environment variable `ANDROID_NDK_HOME` to the Android NDK location. 

### Godot headers
By default the project is configured to checkout the [godot_headers](https://github.com/GodotNativeTools/godot_headers) 
repo as a submodule under the `godot_headers` directory when you run 
the `git submodule init` and `git submodule update` commands.<br>
You can edit the `GODOT_HEADERS_DIR` cmake variable in the `CMakeLists.txt` 
build file if you'd like to provide a different source for the Godot headers.<br>

### Oculus Mobile SDK and Mixed Reality Capture Includes
- Download the [latest version (**Oculus Mobile SDK** 20.0 (API 1.37.0) or higher)](https://developer.oculus.com/downloads/package/oculus-mobile-sdk/)
of the Oculus Mobile SDK into the 
`ovr_sdk_mobile` directory (create the directory if it doesn't exist)
- Download the [latest version (**OVRMRCLib** 2.0)](https://developer.oculus.com/downloads/package/ovrmrclib/) and upack it
  into the `ovr_sdk_mobile\OVRMrcShimLib` directory (create the directory if it doesn't exist)
- If needed, update the `OVR_ROOT_DIR` cmake variable in the the `CMakeLists.txt` build file to point to the Oculus Mobile SDK 
containing folder


### Build
**Note**: Ensure you're using the **Android SDK**'s version of `cmake`.<br><br>
In the project root directory:
 - Navigate to the `build` directory: `cd build`
 - Run:
```
cmake -GNinja ..
cmake --build .
```

Once the build successfully completes, the plugin and its dependencies shared libraries can be found in the 
default output location: `release/addons/godot_ovrmobile/libs/<arch>`

### Deployment
When exporting the project apk in Godot, the following Android export 
`Xr Features` options should be set:
- `Xr Mode` must be set to `Oculus Mobile VR`.
- `Degrees of Freedom`:
  - For Oculus Quest this must be set to `6DOF`
- `Hand Tracking`: 
  - Select `None` if your app doesn't need hand tracking
  - Select `Optional` if your app can use hand tracking, but doesn't require it (i.e: also works with controllers).
  - Select `Required` if your app only uses hand tracking.

## License

- This project is released under the MIT license.
- Please check the [Oculus Mobile SDK license](https://developer.oculus.com/licenses) for information
about the Oculus Mobile SDK used in this project.
