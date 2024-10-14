#include <EnableInterrupt.h>
#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

// 7_segment
const int APIN1 = 2;
const int APIN2 = 3;
const int APIN3 = 4;
const int APIN4 = 5;
const int APIN5 = 6;
const int APIN6 = 7;
const int APIN7 = 8;
const int APIN8 = 9;

// 수동 버저
const int BUZZERPIN = 10;

// button
const int BUTTONPIN = 13; 

int songIndex = 0;  // 현재 연주 중인 음계 인덱스
unsigned long previousMillis = 0;  // 이전 시간 기록
unsigned long currentMillis = 0;  // 현재 시간 기록
unsigned long pauseStartTime = 0;  // 일시정지 시작 시간
unsigned long songDuration = 0;


bool checkIsPaused = false;
bool isPaused = false;  // 일시정지 상태
bool buttonPressed = false; // 버튼이 눌렸는지 확인

// 교과.. {x, y, z} 
// x: 음의 높이 0(낮은 시b) -> 10(높은 미b) malodyIndex
// y: 쉼표 여부
// z: 음의 길이 1(16분 음표) -> 16(온음표)  // 1 => 0.125ms
// maxIndex = 83
const int schoolSong[84][3] = 
{
  {-1, 1, 0}, // 처음 0초 쉬기 (index 맞추기 위해..)
  {7, 0, 8}, // 남
  {7, 0, 4}, // 산
  {8, 0, 4}, // 이
  {7, 0, 4}, // 영
  {6, 0, 3}, // 을
  {5, 0, 1}, // 건
  {4, 0, 8}, // 너
  {0, 0, 6}, // 바
  {1, 0, 2}, // 라
  {2, 0, 4}, // 보
  {0, 0, 4}, // 이
  {4, 0, 12}, // 고
  {-1, 1, 4}, // (쉼표)

  {5, 0, 6}, // 뒤
  {4, 0, 2}, // 로
  {3, 0, 8}, // 는
  {7, 0, 4}, // 관
  {6, 0, 3}, // 악
  {5, 0, 1}, // 산
  {4, 0, 8}, // 이
  {4, 0, 6}, // 높 
  {5, 0, 2}, // 이
  {6, 0, 4}, // 솟
  {7, 0, 4}, // 았 
  {8, 0, 12}, // 네
  {4, 0, 4}, // 한
  
  {9, 0, 8}, // 강
  {9, 0, 4}, // 수
  {8, 0, 4}, // 구
  {7, 0, 4}, // 비
  {6, 0, 4}, // 치
  {5, 0, 8}, // 는
  {8, 0, 8}, // 노
  {8, 0, 4}, // 들
  {7, 0, 4}, // 의
  {6, 0, 4}, // 강
  {5, 0, 4}, // -
  {4, 0, 4}, // 변
  {2, 0, 3}, // 명
  {1, 0, 1}, // 수

  {0, 0, 8}, // 대
  {-1, 1, 2}, // (쉼표)
  {7, 0, 2}, // 송
  {7, 0, 2}, // 림
  {6, 0, 2}, // 속
  {5, 0, 8}, // 에
  {-1, 1, 4}, // (쉼표)
  {5, 0, 4}, // 우
  {4, 0, 8}, // 뚝
  {5, 0, 4}, // 선
  {6, 0, 4}, // 중
  {7, 0, 12}, // 앙
  {-1, 1, 4}, // (쉼표)

  {2, 0, 3}, // 의
  {3, 0, 1}, // 에
  {4, 0, 2}, // 죽
  {-1, 1, 2}, // (쉼표)
  {4, 0, 8}, // 고
  {3, 0, 3}, // 참
  {4, 0, 1}, // 에
  {5, 0, 2}, // 삶
  {-1, 1, 2}, // (쉼표)
  {5, 0, 8}, // 이
  {4, 0, 6}, // 모
  {7, 0, 2}, // 교
  {7, 0, 4}, // 의
  {8, 0, 4}, // 정
  {9, 0, 12}, // 신
  {9, 0, 4}, // 세
  
  {9, 0, 8}, // 계
  {9, 0, 2}, // -
  {9, 0, 2}, // 에
  {8, 0, 2}, // 빛
  {9, 0, 2}, // 내
  {10, 0, 12}, // 세
  {10, 0, 3}, // 우
  {10, 0, 1}, // 리
  {4, 0, 6}, // 중
  {5, 0, 2}, // 앙
  {6, 0, 4}, // 대
  {8, 0, 4}, // 학
  {7, 0, 12}, // 교
  {-1, 1, 4}, // (쉼표)
};


// 멜로디 주파수
const int melody[] = {233, 262, 294, 311, 349, 392, 440, 466, 523, 587, 622}; // 0:시b 1:도 2:레 3:미b 4:파 5:솔 6:라 7:시b 8:도 9:레 10:미b

const int segment[7][8] = 
{
  {1, 1, 1, 1, 1, 1, 1, 1}, // B // 시b
  {1, 0, 0, 1, 1, 1, 0, 0}, // C // 도
  {1, 1, 1, 1, 1, 1, 0, 0}, // D // 레
  {1, 0, 0, 1, 1, 1, 1, 1}, // E // 미b
  {1, 0, 0, 0, 1, 1, 1, 0}, // F // 파
  {1, 0, 1, 1, 1, 1, 1, 0}, // G // 솔
  {1, 1, 1, 0, 1, 1, 1, 0}, // A // 라
};


void  segmentControl(int melodyIndex)
{
  int segmentIndex = melodyIndex % 7;

  if (melodyIndex == -1) // stop 시
  {
    for (int i = 0; i < 8; i++)
      digitalWrite(i + 2, LOW);
    return ;
  }

  for (int i = 0; i < 8; i++)
  {
    if(segment[segmentIndex][i])
      digitalWrite(i + 2, HIGH);
    else
      digitalWrite(i + 2, LOW);
  }
}

void buttonISR() 
{
    buttonPressed = true;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(APIN1, OUTPUT);
  pinMode(APIN2, OUTPUT);
  pinMode(APIN3, OUTPUT);
  pinMode(APIN4, OUTPUT);
  pinMode(APIN5, OUTPUT);
  pinMode(APIN6, OUTPUT);
  pinMode(APIN7, OUTPUT);
  pinMode(APIN8, OUTPUT);

  digitalWrite(APIN1, LOW);
  digitalWrite(APIN2, LOW);
  digitalWrite(APIN3, LOW);
  digitalWrite(APIN4, LOW);
  digitalWrite(APIN5, LOW);
  digitalWrite(APIN6, LOW);
  digitalWrite(APIN7, LOW);
  digitalWrite(APIN8, LOW);
  
  lcd.init();
  lcd.backlight();
  pinMode(BUTTONPIN, INPUT_PULLUP);
  enableInterrupt(BUTTONPIN, buttonISR, FALLING); // 버튼 눌림 감지

  songDuration = schoolSong[songIndex][2] * 125;
  previousMillis = millis();
  Serial.begin(115200);
  Serial.println("setup!");
}

void  lcdStop()
{
  segmentControl(-1);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("0 Hz");
}

void  lcdStart(int melodyIndex)
{
  segmentControl(melodyIndex);
  lcd.clear();
  lcd.setCursor(0, 0);
  String str = String(melody[melodyIndex]);
  Serial.println(str);
  lcd.print(str);
  lcd.print(" Hz");
}


void loop() {
  
  currentMillis = millis();  // 현재 시간 확인

  // 버튼이 눌리면 일시정지 또는 재개
  if (buttonPressed) {
    Serial.println("stop...");
    isPaused = !isPaused;
    buttonPressed = false;
    if (isPaused) {
      noTone(BUZZERPIN);
      lcdStop();
      pauseStartTime = currentMillis - previousMillis;  // 남은 시간 기록
    } else {
      previousMillis = currentMillis - pauseStartTime;  // 재개 시 남은 시간으로 재설정
      if (schoolSong[songIndex][0] != -1)
      {
        tone(BUZZERPIN, melody[schoolSong[songIndex][0]]);
        lcdStart(schoolSong[songIndex][0]);
      }
    }
  }

  // 일시정지 상태가 아닐 때만 음을 재생
  if (!isPaused) {
    if (currentMillis - previousMillis >= songDuration) {
      songIndex += 1;
      if (songIndex == 84) // 완곡했으면, 2초 쉬었다가 다시 재생.
      {
        noTone(BUZZERPIN);
        lcdStop();
        Serial.println("end");
        delay(1950);
        songIndex = 1;
        currentMillis = millis();
      }
      previousMillis = currentMillis;
      noTone(BUZZERPIN);
      delay(50); // 음의 간격을 띄워주기 위한 짧은 delay
      songDuration = schoolSong[songIndex][2] * 125 - 50; // 1초에 4분 음표 2개
      if (schoolSong[songIndex][0] != -1)
      { // 현재 음계 재생
        tone(BUZZERPIN, melody[schoolSong[songIndex][0]]);
        lcdStart(schoolSong[songIndex][0]);
      }
      else
      {
        noTone(BUZZERPIN);
        lcdStop();
      }
    }
  }
}
