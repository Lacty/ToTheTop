
```diff
// ofxJsonSettings.h
+// rename Settigs to ofxJson
+using ofxJson = Settings;
```

```diff
// ofxSceneManager.cpp
// ofxSceneManager::ofxSceneManager()
-curtainDropTime = 0.5f;
-curtainRiseTime = 0.5f;
+curtainFropTime = 0.0f;
+curtainRiseTime = 0.0f;
```
