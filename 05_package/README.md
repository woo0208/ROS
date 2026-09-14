# ROS 2 핵심 개념 정리

## 1. 패키지 (Package)

**패키지 = ROS 2 프로그램을 묶어 놓은 하나의 단위**입니다.

노드, 메시지, 서비스, 액션, 설정 파일, 실행 파일 등을 하나의 패키지 안에 넣어 관리합니다.

예:

    my_robot_package/
    ├── package.xml
    ├── setup.py
    ├── my_robot/
    │   ├── publisher.py
    │   └── subscriber.py
    └── launch/
        └── robot.launch.py


---

## 2. 노드 (Node)

**노드 = ROS 2에서 실제로 일을 수행하는 실행 단위**입니다.

예를 들어 로봇에서:

    카메라 노드
        ↓
    이미지 데이터 발행

    모터 제어 노드
        ↓
    모터 구동

    LiDAR 노드
        ↓
    거리 데이터 발행

하나의 프로그램 안에 여러 기능을 넣을 수도 있지만,
ROS에서는 기능별로 노드를 나누는 경우가 많습니다.

즉,

> **노드는 ROS 2 시스템에서 동작하는 하나의 독립적인 작업자**

라고 생각하면 쉽습니다.

---

## 3. 메시지 (Message)

**메시지 = 노드끼리 주고받는 데이터의 형식**입니다.

예를 들어 온도 센서가 다음 데이터를 보낸다고 해보겠습니다.

    온도: 25.3℃

ROS 2에서는 이런 데이터를 특정 메시지 타입으로 정의합니다.

예:

    std_msgs/msg/Float32

실제 데이터는:

    data: 25.3

처럼 전달됩니다.

즉,

> **메시지는 노드 간에 전달되는 데이터**

입니다.

---

## 4. 메시지 통신 (Message Communication)

**메시지 통신 = 노드와 노드가 메시지를 이용해서 데이터를 주고받는 것**입니다.

ROS 2에서는 대표적으로 **Topic 통신**을 사용합니다.

예:

    [카메라 노드]
          │
          │ 이미지 메시지
          ▼
       /camera/image
          │
          ▼
    [영상처리 노드]

ROS 2에서는 이때 **Publisher / Subscriber** 개념을 사용합니다.

    Publisher
        │
        │ Message
        ▼
      Topic
        │
        ▼
    Subscriber

---

## 5. 토픽 (Topic)

**토픽 = 메시지가 이동하는 통신 채널**입니다.

예를 들어:

    /camera/image

라는 토픽이 있다고 하면,

    카메라 노드
        │
        │ Image 메시지
        ▼
     /camera/image
        │
        ├── 영상처리 노드
        └── 녹화 노드

처럼 여러 노드가 사용할 수 있습니다.

중요한 특징은 **비동기 통신**이라는 것입니다.

Publisher는 데이터를 계속 보내고,
Subscriber는 필요할 때 받습니다.

예:

    Publisher → /scan → Subscriber

LiDAR가 계속 거리 데이터를 발행하고
여러 노드가 이를 구독할 수 있습니다.

---

## 6. 서비스 (Service)

**서비스 = 요청(Request)을 보내고 응답(Response)을 받는 통신 방식**입니다.

토픽과 달리 **1회성 요청-응답**에 적합합니다.

예:

    [사용자]
        │
        │ "로봇 팔을 펴줘"
        ▼
    [서비스 서버]
        │
        │ "완료"
        ▼
    [사용자]

ROS 2에서는:

    Client → Request → Service Server
    Client ← Response ← Service Server

구조입니다.

예를 들어:

    /set_motor

서비스에:

    Request:
      speed = 50

을 보내면:

    Response:
      success = true

를 받을 수 있습니다.

### Topic과 Service 차이

| 구분 | Topic | Service |
|---|---|---|
| 방식 | 발행/구독 | 요청/응답 |
| 방향 | 일방적 | 양방향 |
| 특징 | 계속 데이터 전달 | 요청하면 응답 |
| 예 | 센서 데이터 | 모터 켜기 |
| 통신 | 비동기 | 일반적으로 요청 후 응답 대기 |

---

## 7. 액션 (Action)

**액션 = 시간이 오래 걸리는 작업을 요청하고, 진행 상황과 결과까지 받을 수 있는 통신 방식**입니다.

서비스와 비슷하지만 **긴 작업**에 적합합니다.

예를 들어 로봇에게:

> "앞으로 10m 이동해."

라고 명령한다고 생각해보겠습니다.

    Client
      │
      │ 목표: 10m 이동
      ▼
    Action Server
      │
      ├── Feedback: 2m 이동
      ├── Feedback: 5m 이동
      ├── Feedback: 8m 이동
      │
      └── Result: 이동 완료

즉:

    Goal
      ↓
    작업 수행
      ↓
    Feedback
      ↓
    Result

구조입니다.

### Service와 Action의 차이

**Service**

    "모터를 켜줘"
          ↓
    완료됐어?
          ↓
        Yes

**Action**

    "10m 이동해"
          ↓
      2m 이동
          ↓
      5m 이동
          ↓
      8m 이동
          ↓
      10m 완료

따라서 **시간이 오래 걸리는 작업에는 Action**이 적합합니다.

---

## 8. 파라미터 (Parameter)

**파라미터 = 노드의 동작 방식을 설정하는 값**입니다.

예를 들어 카메라 노드에:

    image_width = 640
    image_height = 480
    fps = 30

이라는 파라미터가 있을 수 있습니다.

그러면 프로그램 코드를 수정하지 않고
설정값만 바꿀 수 있습니다.

    카메라 노드

    Parameter
     ├── width = 640
     ├── height = 480
     └── fps = 30

예를 들어:

    fps = 30

을

    fps = 60

으로 변경하면 카메라 노드의 동작 설정이 바뀝니다.

---

# 전체 관계

ROS 2의 개념을 하나의 로봇으로 연결하면 다음과 같습니다.

                ROS 2
                  │
        ┌─────────┴─────────┐
        │                   │
     Package             Package
        │                   │
     ┌──┴──┐             ┌──┴──┐
     │     │             │     │
   Node   Node          Node   Node
     │     │             │
     │     └──── Topic ──┘
     │          │
     │       Message
     │
     ├──── Service ────→ Request / Response
     │
     ├──── Action ─────→ Goal / Feedback / Result
     │
     └──── Parameter ──→ 설정값

---

# 핵심 정리

| 개념 | 한 줄 정의 | 비유 |
|---|---|---|
| **Package** | ROS 프로그램을 묶는 단위 | 프로젝트/폴더 |
| **Node** | 실제 작업을 수행하는 실행 단위 | 작업자 |
| **Message** | 전달되는 데이터 형식 | 편지 내용 |
| **Message Communication** | 노드 사이에서 데이터를 주고받는 것 | 작업자 간 정보 전달 |
| **Topic** | 메시지가 흐르는 통신 채널 | 방송 채널 |
| **Service** | 요청하고 응답받는 통신 | 주문 → 응답 |
| **Action** | 오래 걸리는 작업을 요청하고 진행상황/결과를 받음 | 배달 주문 → 배송 추적 → 완료 |
| **Parameter** | 노드의 동작을 설정하는 값 | 환경설정 |

---

# 가장 중요한 구분

    계속 데이터를 보내고 싶다
            ↓
          Topic

    요청하고 응답받고 싶다
            ↓
         Service

    오래 걸리는 작업을 시키고
    진행상황도 알고 싶다
            ↓
          Action

    노드의 설정값을 바꾸고 싶다
            ↓
        Parameter

---

# 핵심 관계

**Node ↔ Topic ↔ Message**

그리고 통신 목적에 따라:

    Node
     │
     ├── Topic ───→ Message
     │
     ├── Service ─→ Request / Response
     │
     ├── Action ──→ Goal / Feedback / Result
     │
     └── Parameter → 설정값

이 구조를 이해하면 ROS 2의 기본적인 통신 구조를 이해할 수 있습니다.
