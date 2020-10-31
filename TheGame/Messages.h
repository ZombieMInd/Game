//#pragma once
//#include <string>
//class Messages {
//private:
//	int mission;
//	std::string missionText;
//public:
//	int getCurrentMission(int);
//	int getTextMission(int);
//};
//int Messages::getCurrentMission(int x){
//
//	int mission = 0;
//	if ((x > 0) && (x < 600)) {
//		mission = 0;
//	}
//	if (x > 400) { 
//		mission = 1;
//	} 
//	if (x > 700) {
//		mission = 2;
//	}
//	if (x > 2200) {
//		mission = 3; 
//	}
//
//	return mission;
//}
//
//
//std::string Messages::getTextMission(int currentMission) {
//
//	std::string missionText = "";
//
//	switch (currentMission){
//
//	case 0:
//		missionText = "\nНачальный этап и \nинструкции к игре";
//		break;
//	case 1:
//		missionText = "\nMission 1\n\nВот твоя первая\n миссия, на\n этом уровне \nтебе стоит опасаться\n ... бла-бла-бла ...";
//		break;
//	case 2:
//		missionText = "\nMission 2\n Необходимо решить\n логическую задачку,\n чтобы пройти дальше ";
//		break;
//	case 3:
//		missionText = "\nИ так далее \nи тому подобное....."; 
//		break;
//	}
//
//	return missionText;
//};