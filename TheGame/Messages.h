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
//		missionText = "\n��������� ���� � \n���������� � ����";
//		break;
//	case 1:
//		missionText = "\nMission 1\n\n��� ���� ������\n ������, ��\n ���� ������ \n���� ����� ���������\n ... ���-���-��� ...";
//		break;
//	case 2:
//		missionText = "\nMission 2\n ���������� ������\n ���������� �������,\n ����� ������ ������ ";
//		break;
//	case 3:
//		missionText = "\n� ��� ����� \n� ���� ��������....."; 
//		break;
//	}
//
//	return missionText;
//};