## 1. 메타운영체제, 소프트웨어 플랫폼, 프레임워크, 미들웨어

### 1.1 메타운영체제(Meta-Operating System)

메타운영체제는 일반적인 운영체제 위에서 동작하면서 여러 프로그램과 하드웨어를 하나의 시스템처럼 사용할 수 있도록 공통 기능을 제공하는 소프트웨어 계층을 의미한다.

일반적인 운영체제인 Linux, Windows 등은 CPU 스케줄링, 메모리 관리, 파일 시스템, 장치 드라이버와 같은 컴퓨터의 기본 자원을 직접 관리한다. 반면 메타운영체제는 이러한 기능을 직접 수행하기보다는 기존 운영체제 위에서 **프로세스 간 통신, 하드웨어 추상화, 프로그램 실행 및 관리, 패키지 관리** 등의 기능을 제공한다.

ROS는 전통적으로 이러한 의미에서 **로봇을 위한 메타운영체제**로 설명되어 왔다. ROS 자체가 Linux를 대체하는 운영체제는 아니며 Ubuntu 등의 운영체제 위에서 실행된다.

예를 들어 하나의 자율주행 로봇에 다음과 같은 프로그램이 있다고 가정할 수 있다.

* 카메라 처리 프로그램
* LiDAR 처리 프로그램
* 위치 추정 프로그램
* 경로 계획 프로그램
* 모터 제어 프로그램

ROS는 이러한 프로그램들을 **Node**라는 단위로 구성하고 서로 데이터를 교환할 수 있도록 지원한다.

따라서 ROS에서 메타운영체제라는 표현은 다음과 같이 정리할 수 있다.

> 실제 하드웨어 자원을 직접 관리하는 운영체제가 아니라, 운영체제 위에서 여러 로봇 소프트웨어와 하드웨어를 통합하여 하나의 로봇 시스템으로 동작하도록 지원하는 소프트웨어 환경이다.

---

### 1.2 소프트웨어 플랫폼(Software Platform)

소프트웨어 플랫폼은 응용 프로그램을 개발하고 실행하기 위해 필요한 **공통 실행 환경과 개발 기반**을 의미한다.

일반적으로 소프트웨어 플랫폼에는 다음과 같은 요소가 포함된다.

* API
* 라이브러리
* 개발 도구
* 빌드 시스템
* 패키지 관리 시스템
* 실행 환경
* 디버깅 및 모니터링 도구

ROS 역시 로봇 소프트웨어를 개발하기 위한 플랫폼으로 볼 수 있다.

ROS에서는 다음과 같은 기능을 제공한다.

| 기능        | ROS의 예      |
| --------- | ----------- |
| 프로그램 단위   | Node        |
| 데이터 통신    | Topic       |
| 요청/응답 통신  | Service     |
| 장시간 작업 요청 | Action      |
| 좌표계 관리    | TF/TF2      |
| 시각화       | RViz        |
| 데이터 기록    | rosbag      |
| 빌드        | colcon      |
| 패키지 관리    | ROS Package |

현재 ROS 공식 문서에서도 ROS를 로봇 애플리케이션 개발을 지원하는 **소프트웨어 라이브러리와 도구의 집합**으로 설명한다.

따라서 ROS는 단순한 통신 라이브러리보다 넓은 개념이며, 로봇 개발에 필요한 여러 기능을 제공하는 **종합적인 로봇 소프트웨어 플랫폼**이라고 할 수 있다.

---

### 1.3 프레임워크(Framework)

프레임워크는 소프트웨어를 개발할 때 프로그램의 **전체적인 구조와 동작 방법을 미리 정의해 놓은 개발 틀**이다.

일반적인 라이브러리는 개발자가 필요한 함수를 직접 호출하여 사용하지만, 프레임워크는 개발자가 프레임워크가 정의한 구조에 맞추어 프로그램을 작성한다는 특징이 있다.

ROS에서는 프로그램을 다음과 같은 구조로 작성하도록 한다.

```text
Node
 ├─ Publisher
 ├─ Subscriber
 ├─ Service
 ├─ Client
 ├─ Action
 └─ Parameter
```

예를 들어 카메라 Node가 영상 데이터를 Topic으로 발행하면 객체인식 Node가 해당 Topic을 구독하는 형태로 프로그램을 설계할 수 있다.

ROS 2의 주요 인터페이스는 다음 세 가지이다.

* **Topic**: 연속적인 데이터 스트림 전달
* **Service**: 요청과 응답
* **Action**: 시간이 필요한 작업을 요청하고 중간 진행 상태와 결과 전달

따라서 ROS는 개발자에게 Node, Topic, Service, Action 등의 구조를 제공하므로 **로봇 소프트웨어 개발 프레임워크**로도 볼 수 있다.

---

### 1.4 미들웨어(Middleware)

미들웨어는 운영체제와 응용 프로그램 사이에서 여러 프로그램 또는 여러 컴퓨터가 서로 통신할 수 있도록 중간에서 연결해 주는 소프트웨어 계층이다.

분산 로봇 시스템에서는 센서, 제어기, PC 등이 서로 다른 장치에서 동작할 수 있기 때문에 이들 사이의 통신을 처리하는 기능이 필요하다.

미들웨어는 일반적으로 다음 기능을 담당한다.

* 프로그램 간 통신
* 네트워크 통신
* 데이터 직렬화/역직렬화
* Publisher/Subscriber 연결
* 노드 또는 통신 상대 검색(Discovery)
* 데이터 전송 신뢰성 관리
* QoS(Quality of Service) 관리

ROS 2에서는 `RMW(ROS Middleware)`라는 추상화 계층을 통해 실제 미들웨어에 접근한다.

```text
ROS Application
      ↓
rclcpp / rclpy
      ↓
rcl
      ↓
RMW
      ↓
DDS / RTPS, Zenoh 등
      ↓
Network
```

ROS 공식 문서에 따르면 RMW는 ROS 2 소프트웨어 스택과 실제 통신 미들웨어를 연결하는 인터페이스이다. DDS 계열 미들웨어는 Discovery, Publish/Subscribe, Service의 Request/Reply 및 메시지 직렬화 등을 담당한다.

---

### 1.5 네 가지 개념 비교

| 구분        | 목적                       | ROS와의 관계                       |
| --------- | ------------------------ | ------------------------------ |
| 메타운영체제    | 기존 OS 위에서 분산 시스템을 통합 관리  | ROS를 설명하는 전통적 표현               |
| 소프트웨어 플랫폼 | 프로그램 개발·실행에 필요한 전체 환경 제공 | ROS의 라이브러리, 도구, API 등          |
| 프레임워크     | 프로그램 구조와 개발 방법 제공        | Node, Topic, Service, Action 등 |
| 미들웨어      | 서로 다른 프로그램/장치 간 통신 담당    | ROS 2의 RMW 및 DDS/RTPS 등        |

즉 ROS는 하나의 용어로만 정의하기보다는 **로봇 개발을 위한 소프트웨어 플랫폼이면서 프레임워크이고, 통신 미들웨어를 포함·활용하는 메타운영체제적 환경**으로 보는 것이 적절하다.

---

# 2. DDS란 무엇이며 ROS에서 DDS의 역할은 무엇인가?

## 2.1 DDS란?

DDS는 **Data Distribution Service**의 약자로, OMG(Object Management Group)에서 표준화한 **실시간·분산 시스템용 데이터 중심 Publish/Subscribe 통신 표준**이다.

OMG는 DDS를 실시간 및 임베디드 시스템의 Publish/Subscribe 통신을 직접 지원하는 국제 미들웨어 표준으로 설명하고 있다.

DDS의 기본적인 구조는 다음과 같다.

```text
Publisher
    │
    │ Topic : /camera/image
    ▼
DDS Middleware
    │
    ├──────── Subscriber A
    │
    └──────── Subscriber B
```

Publisher는 특정 Topic에 데이터를 발행하고, 해당 Topic에 관심 있는 Subscriber가 데이터를 수신한다.

---

## 2.2 DDS의 주요 특징

### ① Publish/Subscribe 통신

송신자와 수신자를 직접 연결하지 않고 **Topic을 중심으로 데이터를 교환**한다.

예를 들어 다음과 같이 구성할 수 있다.

```text
LiDAR Node
     ↓
 /scan Topic
     ↓
 ┌──────────────┐
 │              │
Localization   Obstacle Detection
```

LiDAR 프로그램은 데이터를 누가 사용할지 알 필요 없이 `/scan` Topic에 데이터를 발행하면 된다.

---

### ② 자동 검색(Discovery)

DDS는 네트워크에 연결된 Publisher와 Subscriber를 자동으로 검색할 수 있다.

ROS 1에서는 `roscore`라는 중앙 Master가 노드 검색을 담당했지만 ROS 2의 DDS 기반 통신에서는 **분산 Discovery**가 가능하다.

따라서 중앙 Master 하나가 반드시 존재해야 하는 구조에서 벗어날 수 있다.

---

### ③ QoS(Quality of Service)

DDS의 중요한 특징 중 하나는 통신 조건에 따라 데이터 전달 방식을 설정할 수 있다는 것이다.

대표적인 QoS 정책에는 다음과 같은 것들이 있다.

| QoS         | 의미              |
| ----------- | --------------- |
| Reliability | 데이터 전송 신뢰성      |
| Durability  | 이전 데이터 보존 여부    |
| History     | 과거 메시지 저장 방식    |
| Depth       | 저장할 메시지 개수      |
| Deadline    | 데이터 전달 시간 조건    |
| Lifespan    | 데이터의 유효 시간      |
| Liveliness  | 통신 상대의 생존 여부 판단 |

예를 들어 카메라 영상과 로봇 제어 명령은 필요한 통신 특성이 다르다.

카메라는 초당 수십 장의 영상이 계속 들어오기 때문에 일부 프레임이 손실되더라도 최신 데이터를 빠르게 받는 것이 중요할 수 있다.

반면 중요한 제어 명령이나 상태 정보는 데이터가 손실되지 않는 것이 중요할 수 있다.

ROS 2에서는 DDS의 이러한 기능을 이용해 통신 목적에 맞는 QoS를 설정할 수 있다. ROS 공식 문서에서도 ROS 2가 DDS를 기반으로 다양한 QoS 정책을 지원하며, 신뢰성 높은 TCP와 유사한 통신부터 UDP와 같은 Best-Effort 통신까지 설정할 수 있다고 설명한다.

---

## 2.3 ROS 2에서 DDS의 역할

ROS 2의 소프트웨어 구조를 단순화하면 다음과 같다.

```text
사용자 프로그램
(rclcpp / rclpy)
        ↓
       rcl
        ↓
       RMW
        ↓
Fast DDS / Cyclone DDS / Connext DDS 등
        ↓
UDP/TCP 등의 네트워크
```

ROS 개발자는 일반적으로 DDS API를 직접 사용하지 않는다.

예를 들어 C++에서는 다음과 같이 ROS 2 API를 사용한다.

```cpp
publisher_->publish(msg);
```

내부에서는 다음과 같은 흐름이 발생한다.

```text
ROS Publisher
      ↓
rclcpp
      ↓
rcl
      ↓
RMW
      ↓
DDS Publisher
      ↓
Network
      ↓
DDS Subscriber
      ↓
ROS Subscriber
```

즉 DDS는 ROS 2의 **하위 통신 기반** 역할을 담당한다.

구체적인 역할은 다음과 같다.

1. Node 사이의 데이터 전달
2. Publisher와 Subscriber의 자동 검색
3. Topic 기반 Publish/Subscribe 통신
4. 메시지 직렬화 및 전송
5. 분산 네트워크 통신
6. QoS를 이용한 통신 품질 관리
7. 실시간 시스템에 적합한 데이터 전달 구조 제공

ROS 2 공식 문서에서는 DDS/RTPS 기반 미들웨어가 Discovery, Serialization, Transport를 담당한다고 설명한다.

다만 **현재 ROS 2가 DDS만 사용할 수 있는 것은 아니다.**

ROS 2는 특정 미들웨어에 종속되지 않도록 `RMW`라는 추상화 계층을 사용하고 있으며, 최근에는 Zenoh와 같은 비-DDS 미들웨어도 사용할 수 있다. 따라서 정확하게 표현하면 **DDS/RTPS는 ROS 2가 처음부터 채택한 주요 미들웨어 기반이며, RMW를 통해 다양한 DDS 구현체 또는 다른 미들웨어를 선택할 수 있다.**

대표적인 DDS 구현체에는 다음과 같은 것들이 있다.

* eProsima Fast DDS
* Eclipse Cyclone DDS
* RTI Connext DDS
* GurumDDS

---

# 3. ROS를 응용한 제품 및 자율주행 프로젝트 사례

## 3.1 사례 1 — Autoware 자율주행 플랫폼

**Autoware**는 ROS를 기반으로 개발된 오픈소스 자율주행 소프트웨어 프로젝트이다.

Autoware Foundation은 Autoware를 ROS 기반 자율주행 시스템으로 설명하며, 실제 상용 자율주행 시스템 배포를 목표로 하고 있다.

Autoware에는 다음과 같은 자율주행 기능이 포함된다.

```text
Camera / LiDAR / Radar
        ↓
     Sensing
        ↓
    Perception
        ↓
   Localization
        ↓
     Planning
        ↓
     Control
        ↓
Vehicle
```

주요 기능은 다음과 같다.

* Camera/LiDAR/Radar 센서 처리
* 객체 인식
* 자기 위치 추정
* 경로 계획
* 장애물 회피
* 차량 제어
* 자율주행 시뮬레이션

현재 Autoware는 ROS 2를 기반으로 개발되고 있으며 실제 차량을 대상으로 `ros2 launch`를 통해 Sensing, Localization, Perception, Planning, Control 등의 모듈을 실행할 수 있다.

Autoware Foundation은 Autoware가 **30종 이상의 차량 형태와 20개국 이상**에서 활용되는 프로젝트라고 설명하고 있다.

따라서 Autoware는 ROS가 연구용 로봇을 넘어 **자동차 자율주행 소프트웨어 플랫폼으로 활용되는 대표적인 사례**이다.

---

## 3.2 사례 2 — TIER IV Robotaxi 프로젝트

TIER IV는 Autoware를 기반으로 실제 자율주행 차량과 서비스를 개발하고 있는 일본 기업이다.

TIER IV는 Autoware 기반 자율주행 시스템을 세계 여러 지역에서 구현해 왔으며 Autoware가 Linux 및 ROS 미들웨어 위에서 동작한다고 설명한다.

대표적인 사례가 **도쿄 Robotaxi 실증 프로젝트**이다.

TIER IV는 도쿄 오다이바와 니시신주쿠에서 Robotaxi 실증시험을 실시했다. 니시신주쿠 시험에서는 승객이 호출 애플리케이션으로 목적지를 선택하고 차량이 지정된 경로를 자율주행했으며, 누적 시험 거리는 약 **622 km**였다.

또한 TIER IV는 Autoware에 맞게 센서를 구성한 Robotaxi 프로토타입도 제작하고 있다.

따라서 이 사례는 다음과 같은 의미가 있다.

> ROS 기반 자율주행 기술이 단순한 대학 연구 프로젝트가 아니라 실제 도심 Robotaxi와 상용화를 목적으로 한 차량 개발에도 사용되고 있다는 사례이다.

---

## 3.3 사례 3 — Clearpath Robotics의 Husky, Jackal 등 모바일 로봇

Clearpath Robotics는 연구·산업용 자율주행 모바일 로봇을 판매하는 회사이다.

대표적인 제품은 다음과 같다.

* Husky
* Jackal
* Warthog
* Dingo
* Ridgeback
* Boxer

Clearpath는 자사가 공급하는 로봇을 ROS 기반으로 사용할 수 있도록 설계하고 있으며, ROS를 이용하여 자체 실내·실외 자율주행 소프트웨어도 개발한다고 설명하고 있다.

현재 Clearpath의 ROS 2 시스템에서는 모든 지원 플랫폼에 공통적인 ROS 2 API가 제공된다.

예를 들어 이동 명령은 ROS의 `cmd_vel` Topic을 이용한다.

```text
Navigation Node
      ↓
   /cmd_vel
      ↓
Mobile Robot
      ↓
Motor Controller
```

Clearpath의 공식 문서에서도 지원되는 로봇들을 ROS 2 API를 통해 제어할 수 있으며 `cmd_vel` Topic으로 이동 명령을 전달한다고 설명한다.

이는 ROS가 단순한 교육용 소프트웨어가 아니라 **실제 판매되는 로봇 플랫폼의 공식 소프트웨어 인터페이스로도 사용되는 사례**이다.

---

## 3.4 사례 4 — ROS-Industrial의 산업용 로봇 Scan-N-Plan

ROS는 제조업에서도 사용되고 있으며 이를 대표하는 프로젝트가 **ROS-Industrial**이다.

ROS-Industrial은 ROS의 기능을 제조 및 산업용 로봇으로 확장하는 오픈소스 프로젝트이다.

Southwest Research Institute(SwRI)는 ROS 2를 이용하여 산업 고객을 위한 **Collaborative Scan-N-Plan 시스템**을 개발하였다.

이 시스템에서는 Universal Robots의 **UR10e 협동로봇** 등이 사용되었으며, 개발팀은 해당 프로젝트가 실제 산업 고객에게 납품된 초기 ROS 2 상용 시스템 중 하나라고 설명하고 있다.

Scan-N-Plan 시스템은 일반적으로 다음과 같은 과정으로 동작한다.

```text
3D Sensor
    ↓
물체/표면 Scan
    ↓
Point Cloud 처리
    ↓
작업 경로 생성
    ↓
Robot Motion Planning
    ↓
Industrial Robot
```

즉 사람이 로봇의 모든 경로를 미리 프로그래밍하는 대신 센서 데이터를 기반으로 작업 경로를 계산하여 산업용 로봇을 제어하는 데 ROS가 이용된다.

---

# 4. ROS는 산업계에서 실제로 얼마나 사용되는가?

ROS는 처음에는 대학과 연구기관에서 많이 사용되었지만 현재는 산업계 활용 역시 상당한 규모로 확대되었다.

2026년 2월 공개된 **2025 ROS Metrics Report**에 따르면 다음과 같은 통계가 확인된다.

| 지표                               |         2025년 수치 |
| -------------------------------- | ---------------: |
| 연간 ROS Package 다운로드              | **984,135,185회** |
| 2025년 10월 ROS Package 다운로드 고유 IP |     **약 131만 개** |
| 전체 ROS 다운로드 중 ROS 2 비율           |        **91.2%** |
| 확인된 ROS 활용 기업 목록                 |    **1,579개 기업** |
| 제공되는 ROS Package                 |      **34,614개** |
| GitHub `#ROS2` 공개 Repository     |       **3,848개** |

2024년에는 확인된 ROS 사용 기업이 약 1,250개였는데, 2025년 보고서에서는 1,579개로 증가하여 약 **26% 증가**하였다.

또한 ROS-Industrial의 현재 회원 목록에는 다음과 같은 산업 기업들이 포함되어 있다.

* ABB
* BMW
* Boeing
* Caterpillar
* Intel
* Mitsubishi Electric
* Omron
* Siemens
* Universal Robots
* Volvo Group
* Yaskawa
* Yokogawa

등의 제조·자동차·로봇 관련 기업이 참여하고 있다.

2025 ROS-Industrial Conference에서도 Universal Robots의 ROS 인터페이스, Yaskawa 산업용 로봇 응용, igus의 실제 ROS 기반 산업 솔루션 등이 발표되었다.

따라서 ROS는 연구용으로만 사용되는 시스템이라고 보기 어렵고, 현재는 다음 영역에서 실제 활용되고 있다.

* 자율주행 자동차
* AMR/AGV
* 물류 로봇
* 협동로봇
* 산업용 Manipulator
* 의료 로봇
* 드론
* 서비스 로봇
* 연구용 로봇

다만 ROS Metrics의 다운로드 횟수를 곧바로 **실제 로봇 대수**로 해석해서는 안 된다. 패키지 다운로드에는 개발 PC, CI 서버, Docker 환경, 업데이트 및 반복 설치 등이 포함될 수 있고, ROS는 사용자 개인정보 보호를 위해 실제 사용자를 직접 추적하지 않는다. ROS Metrics 역시 이러한 수치를 정확한 사용자 수가 아닌 ROS 생태계의 규모와 변화 방향을 측정하기 위한 **대리지표(Proxy Metric)**로 사용한다고 밝히고 있다.

그럼에도 불구하고 **1,579개 이상의 확인된 기업**, 연간 약 **9.84억 회의 패키지 다운로드**, ROS 2 비중 **91.2%**라는 수치를 고려하면 ROS는 현재 연구·교육 분야를 넘어 실제 로봇 산업에서도 상당한 규모로 사용되는 소프트웨어 생태계라고 판단할 수 있다.

---

# 5. 결론

ROS는 단순한 Robot Operating System이라는 이름과 달리 Linux나 Windows와 같은 일반적인 운영체제는 아니다.

ROS는 운영체제 위에서 동작하면서 로봇 프로그램의 통신과 실행을 지원하기 때문에 **메타운영체제**라고 표현할 수 있으며, 다양한 라이브러리와 개발 도구를 제공한다는 점에서는 **소프트웨어 플랫폼**, Node와 Topic 등의 프로그램 구조를 제공한다는 점에서는 **프레임워크**의 성격도 가지고 있다.

ROS 2에서는 RMW 계층 아래에서 DDS/RTPS와 같은 미들웨어를 이용하여 분산된 Node 사이의 통신을 수행한다. DDS는 Publisher/Subscriber 검색, 메시지 전달, 데이터 직렬화 및 QoS와 같은 통신 기능을 담당한다.

ROS의 실제 활용 사례로는 Autoware 자율주행 플랫폼, TIER IV Robotaxi, Clearpath의 모바일 로봇, ROS-Industrial 기반 산업용 로봇 시스템 등이 있다.

특히 2025년 기준 ROS 관련 패키지 다운로드가 약 9.84억 회에 달하고 1,579개 이상의 기업이 ROS를 사용하는 것으로 확인되고 있기 때문에, ROS는 연구용 로봇 개발도구에서 출발하여 현재는 **자율주행·산업용 로봇·물류·서비스 로봇 등 실제 산업 분야에서도 폭넓게 활용되는 로봇 소프트웨어 플랫폼**으로 발전했다고 볼 수 있다.

---

# 참고자료

1. ROS Developer Documentation — Robot Operating System 공식 문서
2. ROS 2 Documentation — Internal ROS 2 Interfaces
3. ROS 2 Documentation — Different ROS 2 Middleware Vendors
4. ROS 2 Documentation — Quality of Service Settings
5. Object Management Group — Data Distribution Service (DDS)
6. Autoware Foundation — Autoware Overview
7. TIER IV — Autoware 및 Robotaxi 관련 공식 자료
8. Clearpath Robotics — ROS 2 Documentation
9. ROS-Industrial — ROS 2 Collaborative Industrial Scan-N-Plan
10. Open Robotics — 2025 ROS Metrics Report
11. ROS-Industrial — Current Members
