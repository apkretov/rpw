#property strict
#ifndef ENUMERATORS_MQH
#define ENUMERATORS_MQH

enum enmMagic {_1 = 1, _2, _3, _4, Alligator, Test};

enum enmActivate {ActivateIndicator, ActivateTimeFrame};

enum enmKeys { 
   keyTab = 9, 
   keyEnter = 13, 
   keyEsc = 27, 
   keySpace = 32, 
   keyEnd = 35, 
   keyArrowLeft = 37, 
   keyArrowUp, 
   keyArrowRight, 
   keyArrowDown, 
   keyDel = 46, 
   key0 = 48, 
   key1, key2, 
   key3, 
   key4, 
   key5, 
   key6, 
   key7, 
   key8, 
   key9,  
   keyA = 65, 
   keyB, 
   keyC, 
   keyD, 
   keyE, 
   keyF, 
   keyG, 
   keyK = 75,
   keyL,
   keyM,
   keyP = 80,
   keyQ, 
   keyR, 
   keyS, 
   keyT, 
   keyV = 86, 
   keyW, 
   keyX, 
   keyZ = 90, 
   key0Num = 96, 
   key1Num, 
   key2Num, 
   key3Num, 
   key4Num, 
   key5Num, 
   key6Num, 
   key7Num, 
   key8Num, 
   key9Num, 
   keyNumMinus = 109,
   keyNumSlash = 111, 
   keyF5 = 116,
   keyTilde = 192
};

enum enmWM { //The PostMessageA codes @ https://forum.mql4.com/ru/14463
   wmSavePicture = 33054, 
   wmCrossHair = 33233, 
   wmRegression = 33248,
   wmHLine = 33244, 
   wmRectangle = 33247,
   wmTrend = 33257, 
   wmVLine = 33260,
   wmLogin = 35429, 
   wmEsc = 35462, 
   wmLeftArrow 
};

enum enmVK { //bVirtualKey for keybd_event: Virtual keycode that has to be send as key input. The following are the available predefined virtual key codes. @ http://www.codeproject.com/Articles/7305/Keyboard-Events-Simulation-using-keybd-event-funct
   vkTab = 0x09, 
   vkShift, 
   vkCtrl, 
   vkMenu 
}; 

enum enmNCmdShow { 
   showNormal = 1, 
   showMaximized = 3
};

enum enmDirec {direcDown = -1, direcFlat, direcUp};

enum enmTickSteps {pts1 = 1, pts50 = 50, pts100 = 100, pts1000 = 1000};

#endif //ENUMERATORS_MQH