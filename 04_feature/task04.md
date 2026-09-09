# ROS2 통신 및 DDS 관련 조사

## 1. 미들웨어(Middleware)란 무엇인가?

**미들웨어(Middleware)**란 운영체제나 네트워크와 같은 하위 시스템과 응용 프로그램 사이에서 동작하면서, 서로 다른 프로그램들이 데이터를 주고받거나 기능을 사용할 수 있도록 중간에서 서비스를 제공하는 소프트웨어 계층이다.

쉽게 표현하면,

    Application A
          │
          ▼
    ┌──────────────┐
    │  Middleware  │
    └──────────────┘
          │
          ▼
    OS / Network / Hardware

와 같은 구조로 볼 수 있다.

응용 프로그램이 네트워크 통신, 데이터 직렬화, 메시지 전달 등의 기능을 모두 직접 구현하면 개발이 복잡해진다.

미들웨어를 사용하면 이러한 공통 기능을 미들웨어가 담당하기 때문에 응용 프로그램은 실제 기능 구현에 집중할 수 있다.

### 미들웨어의 주요 기능

- 프로그램 간 데이터 통신
- 메시지 전달
- 데이터 직렬화(Serialization) 및 역직렬화
- 서비스 검색
- 분산 시스템 지원
- 네트워크 통신 관리
- 오류 처리
- 보안 기능
- QoS(Quality of Service) 관리

### ROS에서의 미들웨어

ROS에서도 여러 Node가 서로 통신해야 하므로 미들웨어가 필요하다.

ROS1에서는 ROS 전용 통신 방식인 TCPROS 등이 사용되었지만, ROS2에서는 처음부터 기존의 표준화된 통신 미들웨어를 활용하는 방향으로 설계되었으며 대표적으로 DDS가 사용된다.

ROS2에서는 다음과 같은 계층 구조를 가진다.

    ROS2 Application
           │
           ▼
        rclcpp / rclpy
           │
           ▼
           rcl
           │
           ▼
          RMW
    (ROS Middleware Interface)
           │
           ▼
    DDS 등의 Middleware
           │
           ▼
        Network

RMW를 이용하기 때문에 ROS2의 상위 프로그램은 특정 DDS 제품의 API를 직접 사용할 필요가 없다.

즉, 미들웨어는 **응용 프로그램과 운영체제·네트워크 사이에서 통신이나 데이터 교환과 같은 공통 기능을 제공하는 중간 소프트웨어 계층**이라고 할 수 있다.


---

# 2. 분산 컴퓨팅(Distributed Computing)에 대하여 조사하시오.

**분산 컴퓨팅(Distributed Computing)**이란 네트워크로 연결된 여러 개의 독립적인 컴퓨터가 서로 데이터를 교환하면서 하나의 작업이나 시스템을 공동으로 수행하는 컴퓨팅 방식이다.

예를 들어 다음과 같은 시스템을 생각할 수 있다.

    Computer A                Computer B
    ┌───────────┐            ┌───────────┐
    │ Camera    │──Network──▶│ AI        │
    │ Processing│            │ Processing│
    └───────────┘            └─────┬─────┘
                                   │
                              Network
                                   │
                                   ▼
                             ┌───────────┐
                             │ Robot     │
                             │ Controller│
                             └───────────┘

각 컴퓨터는 독립적인 CPU와 메모리를 가지고 있지만 네트워크를 통해 서로 협력한다.

### 분산 컴퓨팅의 특징

#### 1. 여러 컴퓨터 사용

한 대의 컴퓨터가 아니라 여러 대의 컴퓨터가 작업을 나누어 수행한다.

#### 2. 네트워크 통신

컴퓨터들이 물리적으로 분리되어 있기 때문에 TCP/IP 등의 네트워크 통신 기술이 필요하다.

#### 3. 자원 공유

CPU, 저장장치, 센서, 데이터 등의 자원을 여러 시스템에서 공유할 수 있다.

#### 4. 확장성

처리량이 부족하면 새로운 컴퓨터를 추가하여 시스템의 처리 능력을 증가시키는 방식으로 확장할 수 있다.

#### 5. 장애 대응

잘 설계된 분산 시스템에서는 일부 컴퓨터에 문제가 발생하더라도 다른 컴퓨터가 기능을 계속 수행하도록 구성할 수 있다.

### 분산 컴퓨팅의 단점

- 네트워크 지연 발생
- 패킷 손실 가능성
- 컴퓨터 간 시간 동기화 문제
- 통신 장애 가능성
- 시스템 구성 및 디버깅이 복잡함
- 동시성 및 데이터 일관성 문제

### 활용 사례

분산 컴퓨팅은 다음과 같은 분야에서 사용된다.

- 클라우드 컴퓨팅
- 데이터 센터
- 빅데이터 처리
- 분산 데이터베이스
- 스마트 팩토리
- 자율주행 시스템
- 다중 로봇 시스템
- IoT 시스템
- ROS2 기반 로봇 시스템

예를 들어 ROS2에서는 한 컴퓨터에서 Camera Node를 실행하고 다른 컴퓨터에서 AI Node를 실행하며 또 다른 컴퓨터에서 Motor Control Node를 실행할 수 있다.

    PC A                  PC B                 Robot PC
    Camera Node   ───▶   AI Node   ───▶   Control Node

이들이 DDS 기반 네트워크 통신을 이용하여 하나의 로봇 시스템을 구성할 수 있다.


---

# 3. 네트워크 통신 기술에 대하여 조사하라.

**네트워크 통신(Network Communication)**이란 두 개 이상의 컴퓨터나 장치가 네트워크를 통해 데이터를 주고받는 기술을 의미한다.

네트워크 통신을 위해서는 송신자와 수신자가 동일한 통신 규칙인 **프로토콜(Protocol)**을 따라야 한다.

기본적인 데이터 전달 구조는 다음과 같다.

    Application
        │
        ▼
    TCP / UDP
        │
        ▼
        IP
        │
        ▼
    Ethernet / Wi-Fi
        │
        ▼
      Network

## 주요 네트워크 기술

### 1. Ethernet

Ethernet은 유선 LAN에서 가장 널리 사용되는 네트워크 기술이다.

일반적으로 LAN 케이블과 Ethernet 장치를 이용하여 컴퓨터들을 연결한다.

장점은 다음과 같다.

- 높은 전송 속도
- 비교적 안정적인 통신
- 낮은 패킷 손실률
- 산업용 시스템에서 널리 사용

---

### 2. Wi-Fi

Wi-Fi는 무선 LAN 통신 기술이다.

케이블 없이 장치를 네트워크에 연결할 수 있기 때문에 스마트폰, 노트북, IoT 장치, 이동 로봇 등에 많이 사용된다.

다만 무선 환경이므로 간섭, 신호 강도 및 혼잡 상황에 따라 통신 품질이 변할 수 있다.

---

### 3. IP(Internet Protocol)

IP는 네트워크에서 데이터를 목적지 장치까지 전달하기 위한 프로토콜이다.

장치를 구분하기 위해 IP Address를 사용한다.

예:

    Computer A
    IP = 192.168.0.10

    Computer B
    IP = 192.168.0.20

---

### 4. TCP(Transmission Control Protocol)

TCP는 **연결 지향형 전송 프로토콜**이다.

특징은 다음과 같다.

- 연결을 설정한 후 통신
- 데이터 전달 신뢰성 제공
- 데이터 순서 보장
- 손실 데이터 재전송
- 흐름 제어
- 혼잡 제어

따라서 데이터가 정확하게 전달되어야 하는 통신에서 많이 사용된다.

예:

- HTTP/HTTPS
- 파일 전송
- 원격 접속
- MQTT의 일반적인 전송 기반

---

### 5. UDP(User Datagram Protocol)

UDP는 **비연결형 전송 프로토콜**이다.

특징은 다음과 같다.

- 연결 설정 과정이 없음
- 데이터 전달을 보장하지 않음
- 패킷 순서를 보장하지 않음
- TCP보다 프로토콜 오버헤드가 작음
- 낮은 지연시간이 필요한 통신에 유리할 수 있음
- Multicast 통신에 사용할 수 있음

실시간 센서 데이터, 음성, 영상 또는 DDS/RTPS 기반 통신 등에 활용될 수 있다.

### TCP와 UDP 비교

| 항목 | TCP | UDP |
|---|---|---|
| 연결 방식 | 연결 지향 | 비연결 |
| 신뢰성 | 높음 | 기본적으로 보장하지 않음 |
| 순서 보장 | O | X |
| 재전송 | O | X |
| 오버헤드 | 상대적으로 큼 | 상대적으로 작음 |
| Multicast | 지원하지 않음 | 지원 가능 |
| 대표 용도 | 웹, 파일, MQTT 등 | 스트리밍, DDS/RTPS 등 |

---

### 네트워크 통신에서 Port

하나의 컴퓨터에서 여러 프로그램이 네트워크를 사용하기 때문에 어떤 프로그램으로 데이터를 전달할지 구분하기 위해 **Port 번호**를 사용한다.

예:

    IP Address : 192.168.0.10
    Port       : 8080

즉,

    IP Address → 어느 컴퓨터인가?
    Port       → 그 컴퓨터의 어느 통신 프로그램인가?

를 구분한다고 이해할 수 있다.


---

# 4. RTPS(Real-Time Publish Subscribe) 프로토콜에 대하여 조사하시오.

RTPS는 **Real-Time Publish-Subscribe Protocol**의 약자로, 현재 OMG에서는 일반적으로 **DDSI-RTPS(DDS Interoperability Real-Time Publish-Subscribe)**라는 표준으로 정의하고 있다.

RTPS는 DDS 시스템들이 네트워크를 통해 서로 데이터를 주고받기 위해 사용하는 **Wire Protocol(네트워크 상의 통신 규약)**이다.

여기서 중요한 점은

    DDS ≠ RTPS

라는 것이다.

관계를 표현하면 다음과 같다.

    ROS2
      │
      ▼
     RMW
      │
      ▼
     DDS
      │
      ▼
   DDSI-RTPS
      │
      ▼
   UDP/IP 등
      │
      ▼
    Network

### DDS와 RTPS의 관계

DDS는 다음과 같은 기능을 정의하는 **통신 미들웨어 표준**이다.

- Publish / Subscribe
- Topic
- DataWriter
- DataReader
- QoS
- Discovery
- 데이터 관리

반면 RTPS는 서로 다른 DDS 구현체들이 네트워크에서 실제로 어떻게 정보를 주고받을지 정의하는 **상호운용 프로토콜**이다.

예를 들어 서로 다른 DDS 제품을 사용하더라도 표준을 준수한다면 RTPS를 통해 통신할 수 있도록 설계되어 있다.

### RTPS의 주요 구성

DDS에서 Publisher 측에는 DataWriter가 존재하고 Subscriber 측에는 DataReader가 존재한다.

    Publisher
       │
    DataWriter
       │
       │ RTPS
       ▼
    DataReader
       │
    Subscriber

DataWriter가 데이터를 생성하면 RTPS를 통해 적절한 DataReader에게 전달된다.

### RTPS의 주요 특징

- Publish/Subscribe 기반 통신
- DDS 구현체 간 상호운용성 제공
- 분산 환경 지원
- 자동 Discovery 지원
- Reliable / Best-Effort와 같은 전송 정책 지원
- UDP 기반 통신에 널리 사용
- Multicast 및 Unicast 활용 가능
- 실시간·임베디드 분산 시스템을 고려하여 설계

### 주의점

RTPS의 이름에 `Real-Time`이 포함되어 있다고 해서 RTPS를 사용하는 모든 시스템이 자동으로 Hard Real-Time 시스템이 되는 것은 아니다.

실시간성을 만족하기 위해서는 RTOS, 스케줄링, 네트워크 지연, QoS, 하드웨어 등 전체 시스템의 시간 특성을 함께 고려해야 한다.


---

# 5. DDS의 동적 검색(Dynamic Discovery) 기능을 조사하시오.

**Dynamic Discovery**란 DDS 네트워크에 새로운 장치나 통신 Endpoint가 추가되었을 때 별도의 중앙 Master에 수동 등록하지 않아도 서로를 자동으로 발견하고 통신 관계를 설정할 수 있도록 하는 기능이다.

ROS1과 비교하면 차이가 명확하다.

### ROS1

ROS1에서는 Node가 ROS Master에 등록된다.

    Node A ──────▶ ROS Master ◀────── Node B
                        │
                Node 위치 정보 제공
                        │
                        ▼
                A와 B 직접 연결

### ROS2 + DDS

기본적인 DDS 기반 ROS2 환경에서는 중앙 ROS Master가 필요하지 않다.

    Node A  ◀────────▶  Node B
      ▲                  ▲
      │     Discovery    │
      ▼                  ▼
    Node C  ◀────────▶  Node D

DDS의 Discovery 기능을 이용하여 참여자들이 서로를 찾는다.

---

## DDS Discovery의 기본 과정

RTPS 기반 DDS Discovery는 크게 다음 단계로 이해할 수 있다.

### 1단계: Participant Discovery

먼저 네트워크에 어떤 DDS Participant가 존재하는지를 검색한다.

대표적으로 RTPS의

**SPDP(Simple Participant Discovery Protocol)**

가 사용된다.

예를 들어 새로운 ROS2 Node가 실행되면 네트워크의 다른 DDS Participant와 존재 정보를 교환한다.

    Participant A
          │
          │ "나는 여기에 있다"
          ▼
    Network
          │
          ▼
    Participant B

---

### 2단계: Endpoint Discovery

Participant를 찾은 다음에는 각각 어떤 데이터를 Publish하거나 Subscribe하는지 확인해야 한다.

이를 위해

**SEDP(Simple Endpoint Discovery Protocol)**

등을 이용한다.

Endpoint에는 대표적으로 다음이 포함된다.

- DataWriter
- DataReader

예를 들어

    Node A
    Topic : /camera
    Type  : Image
    Publisher

와

    Node B
    Topic : /camera
    Type  : Image
    Subscriber

가 존재한다면 DDS는 이 정보를 바탕으로 서로 통신 가능한 Endpoint를 연결한다.

---

### 3단계: QoS 호환성 확인

Topic 이름이나 데이터 타입만 같다고 무조건 통신하는 것은 아니다.

Publisher와 Subscriber의 QoS 조건도 호환되어야 한다.

예:

    Publisher
    Reliability = Reliable

               ↓ QoS Matching

    Subscriber
    Reliability = Reliable

조건이 호환되면 데이터 통신 관계가 형성된다.

---

## ROS2에서의 Discovery 과정

전체적인 흐름을 단순화하면 다음과 같다.

    Node 실행
       │
       ▼
    Participant Discovery
       │
       ▼
    다른 Participant 발견
       │
       ▼
    Endpoint Discovery
       │
       ▼
    Topic / Type / QoS 정보 확인
       │
       ▼
    호환되는 Publisher ↔ Subscriber 연결
       │
       ▼
    데이터 통신

### Dynamic Discovery의 장점

- ROS Master와 같은 중앙 관리 시스템이 기본적으로 필요하지 않음
- Node를 추가하면 자동 발견 가능
- 분산 시스템 구성에 유리
- 시스템 확장성이 높음
- 중앙 Master 장애에 대한 의존성이 감소

다만 DDS 구현과 네트워크 환경에 따라 Discovery 방식을 변경할 수 있으며, 모든 Discovery가 반드시 Multicast만을 사용하는 것은 아니다.

예를 들어 일부 DDS 구현체에서는 Discovery Server나 정적 Discovery와 같은 별도의 방식을 사용할 수도 있다.


---

# 6. ROS1과 ROS2의 통신 방식의 차이를 설명하시오.

ROS1과 ROS2 모두 Node 간 Topic, Service 등의 통신 기능을 제공하지만 내부 통신 구조에는 큰 차이가 있다.

## ROS1

ROS1은 ROS Master를 중심으로 Node를 검색한다.

    Publisher
        │
        │ 등록
        ▼
    ROS Master
        ▲
        │ 조회
        │
    Subscriber

Publisher와 Subscriber가 상대방의 위치를 확인한 후에는 일반적으로 직접 통신한다.

대표적인 Topic 전송 방식은 TCPROS이다.

따라서 ROS Master가 모든 메시지를 전달하는 것은 아니다.

ROS Master는 주로

- Node 등록
- Topic 등록
- Service 등록
- Publisher/Subscriber 검색

등의 역할을 담당한다.

---

## ROS2

ROS2에서는 초기부터 DDS/RTPS를 주요 미들웨어 기반으로 채택하였다.

DDS 기반 ROS2에서는 ROS1의 ROS Master에 해당하는 중앙 서버가 기본적으로 필요하지 않으며 DDS Discovery를 이용한다.

    Node A  ◀──── DDS/RTPS ────▶ Node B
      ▲                            ▲
      │                            │
      └────────── Node C ──────────┘

또한 DDS의 QoS 기능을 이용하여 통신 방식을 세부적으로 조정할 수 있다.

대표적인 QoS 정책에는 다음이 있다.

- Reliability
- Durability
- History
- Depth
- Deadline
- Lifespan
- Liveliness

### ROS1과 ROS2 비교

| 항목 | ROS1 | ROS2 |
|---|---|---|
| 통신 기반 | ROS 자체 통신 구조 | RMW 기반 미들웨어 구조 |
| 대표 Middleware/Protocol | TCPROS | DDS/RTPS |
| Node Discovery | ROS Master | DDS의 분산 Discovery |
| 중앙 Master | 필요 | DDS 기반 구성에서는 기본적으로 불필요 |
| QoS | 제한적 | 다양한 QoS 제공 |
| 신뢰성 선택 | 주로 TCPROS | Reliable / Best Effort 등 선택 |
| 실시간 시스템 고려 | 제한적 | 보다 적극적으로 고려 |
| 분산 시스템 | 가능하지만 제약 존재 | 분산 환경을 적극적으로 고려 |
| 통신 구현 변경 | 어려움 | RMW를 통해 여러 Middleware 지원 가능 |

※ 현대 ROS2는 RMW 계층을 통해 DDS뿐만 아니라 다른 Middleware 구현도 사용할 수 있다. 그러나 ROS2 설계 당시 핵심 통신 기반으로 채택된 기술은 DDS/RTPS이다.


---

# 7. ROS2에서 DDS 기술을 도입한 이유를 설명하라.

ROS2가 개발될 당시 ROS1의 통신 시스템에는 산업용 및 대규모 로봇 시스템에 적용하기 위한 여러 제한사항이 존재했다.

ROS2 개발 과정에서는 ROS1 통신 방식을 단순히 확장하는 방법뿐 아니라 새로운 Middleware를 직접 개발하는 방법도 검토되었지만, 최종적으로 이미 표준화되고 산업 분야에서 사용되고 있던 DDS를 활용하는 방향이 선택되었다.

## 주요 도입 이유

### 1. 분산 Discovery

ROS1에서는 ROS Master가 필요하다.

    Node A ───▶ ROS Master ◀─── Node B

반면 DDS는 기본적으로 분산 Discovery를 지원하기 때문에 중앙 Master 없이 Participant들이 서로를 발견할 수 있다.

    Node A ◀──────▶ Node B
      ▲              ▲
      └──── Node C ──┘

이에 따라 중앙 Discovery 시스템에 대한 의존성을 줄일 수 있다.

---

### 2. QoS 지원

로봇에서는 데이터 종류마다 필요한 통신 특성이 다르다.

예를 들어 Camera 데이터는

    빠른 최신 데이터 전달
            >
    모든 Frame의 완벽한 전달

이 중요할 수 있다.

반대로 중요한 제어 명령에서는

    데이터 전달 신뢰성

이 더 중요할 수 있다.

DDS에서는 이를 QoS를 이용하여 조절할 수 있다.

예:

    Camera
    Reliability = Best Effort

    Control Command
    Reliability = Reliable

ROS2에서는 Reliability뿐 아니라 History, Durability, Deadline, Lifespan, Liveliness 등의 정책도 사용할 수 있다.

---

### 3. 실시간 시스템에 적합한 기능

DDS는 처음부터 실시간 및 임베디드 분산 시스템을 주요 사용 분야 중 하나로 고려한 표준이다.

따라서 ROS2가 산업용 로봇, 자동차, 임베디드 시스템 등의 영역으로 확장되는 데 유리하다.

---

### 4. 표준화된 기술

DDS는 OMG(Object Management Group)의 공개 표준이다.

ROS 개발팀이 새로운 네트워크 Middleware 전체를 처음부터 직접 만들고 유지하는 것보다 기존에 개발되고 검증된 표준 Middleware를 사용할 수 있다는 장점이 있다.

---

### 5. 여러 DDS 구현체 사용 가능

DDS는 하나의 회사가 만든 특정 프로그램이 아니라 표준이기 때문에 여러 업체나 오픈소스 프로젝트가 구현체를 개발할 수 있다.

대표적인 예는 다음과 같다.

- Eclipse Cyclone DDS
- eProsima Fast DDS
- RTI Connext DDS
- GurumDDS

ROS2에서는 RMW(ROS Middleware Interface)를 두어 상위 ROS 프로그램과 실제 Middleware를 분리하였다.

    ROS2 Application
          │
          ▼
         RMW
          │
     ┌────┼─────┐
     ▼    ▼     ▼
    DDS A DDS B Other Middleware

따라서 특정 Middleware 구현체에 완전히 종속되는 것을 줄일 수 있다.

---

### 6. 분산 로봇 시스템에 적합

실제 로봇에서는 모든 기능이 하나의 컴퓨터에서 실행된다고 볼 수 없다.

예를 들어

    Camera Computer
          │
          ▼
    AI Computer
          │
          ▼
    Motion Controller
          │
          ▼
       Robot

처럼 여러 장치가 협력할 수 있다.

DDS는 이러한 분산형 Publish/Subscribe 통신을 주요 목적으로 설계되어 ROS2의 분산 로봇 시스템 구조와 잘 맞는다.

### 정리

ROS2가 DDS를 도입한 주요 이유는 다음과 같이 정리할 수 있다.

1. 중앙 Master에 의존하지 않는 분산 Discovery
2. 다양한 QoS 기능
3. 실시간 및 임베디드 시스템 지원
4. 산업 표준 활용
5. 여러 Middleware 구현체 선택 가능
6. 대규모 분산 시스템에 대한 확장성
7. ROS 개발팀이 자체 통신 Middleware 전체를 유지해야 하는 부담 감소

즉, **ROS1의 연구용 로봇 중심 통신 구조를 넘어 산업용·분산형·실시간 로봇 시스템까지 지원하기 위해 DDS가 ROS2의 핵심 통신 기반으로 도입되었다고 볼 수 있다.**


---

# 8. 비슷한 통신 기술인 MQTT와 DDS의 차이를 설명하라.

MQTT와 DDS는 모두 **Publish/Subscribe** 방식을 사용할 수 있다는 공통점이 있지만 구조와 목적에는 큰 차이가 있다.

## MQTT

MQTT(Message Queuing Telemetry Transport)는 IoT 환경에서 많이 사용되는 경량 Publish/Subscribe 메시징 프로토콜이다.

MQTT의 가장 중요한 특징은 **Broker 중심 구조**라는 것이다.

    Publisher
        │
        │ Publish
        ▼
    ┌──────────┐
    │  Broker  │
    └──────────┘
       │     │
       ▼     ▼
    Subscriber A
    Subscriber B

Publisher가 Subscriber에게 직접 메시지를 보내는 것이 아니라 Broker에게 데이터를 전송한다.

Broker는 해당 Topic을 구독하고 있는 Client들에게 메시지를 전달한다.

예:

    Publisher
       │
       │ Topic = factory/temperature
       ▼
    MQTT Broker
       │
       ├────────▶ PC
       │
       └────────▶ Smartphone

### MQTT 특징

- Broker 기반
- Publish/Subscribe
- TCP 기반으로 널리 사용
- 비교적 단순하고 경량
- IoT 환경에서 널리 사용
- 저성능 장치에서도 사용하기 쉬움
- 인터넷 또는 클라우드 시스템과 연결하기 용이

---

## DDS

DDS도 Publish/Subscribe 방식을 사용하지만 일반적인 DDS 구성에서는 MQTT와 같은 중앙 Message Broker가 필요하지 않다.

    Publisher
        │
        │
        ├────────▶ Subscriber A
        │
        └────────▶ Subscriber B

DDS Discovery를 통해 Publisher와 Subscriber가 서로를 발견하고 통신할 수 있다.

DDS는 단순한 메시지 전달보다 **Data-Centric 통신**을 지향하며 Topic과 데이터 타입 및 QoS 등을 기반으로 통신 관계를 구성한다.

---

## MQTT QoS

MQTT에도 QoS라는 개념이 존재한다.

대표적으로 다음 세 단계가 있다.

    QoS 0 = At most once
    QoS 1 = At least once
    QoS 2 = Exactly once

이는 주로 MQTT 메시지의 **전달 보장 수준**을 의미한다.

---

## DDS QoS

DDS의 QoS는 훨씬 다양한 통신 특성을 제어한다.

예:

- Reliability
- Durability
- History
- Depth
- Deadline
- Lifespan
- Liveliness
- Resource Limits 등

따라서

    MQTT QoS
        ↓
    주로 메시지 전달 보장 수준

    DDS QoS
        ↓
    데이터 전달의 신뢰성 + 보존 + 시간 조건
    + 상태 관리 + 자원 관리 등

이라는 차이가 있다.

---

## MQTT와 DDS 비교

| 항목 | MQTT | DDS |
|---|---|---|
| 방식 | Publish/Subscribe | Data-Centric Publish/Subscribe |
| 구조 | Broker 기반 | 일반적으로 Brokerless 분산 구조 |
| 중앙 서버 | Broker 필요 | 기본 구조에서 불필요 |
| Discovery | 알려진 Broker에 Client 연결 | DDS Dynamic Discovery 지원 |
| 대표 전송 | TCP | RTPS, 일반적으로 UDP/IP 활용 가능 |
| QoS | 0, 1, 2 전달 수준 | 다양한 세부 QoS 정책 |
| 데이터 모델 | Topic 기반 메시징 | Topic + Type 기반 데이터 중심 모델 |
| 실시간 시스템 | 주목적이 아님 | 실시간·임베디드 시스템을 고려 |
| 시스템 복잡도 | 비교적 낮음 | 상대적으로 높음 |
| 네트워크 부하 | 비교적 경량 | 설정 및 Discovery에 따라 증가 가능 |
| 주요 활용 | IoT, Cloud, Telemetry | Robot, 자동차, 산업, 국방, 분산 실시간 시스템 |

---

## MQTT와 DDS를 쉽게 비교하면

### MQTT

    Sensor
      │
      ▼
    Broker
      │
      ├────▶ Cloud
      ├────▶ PC
      └────▶ Smartphone

중앙 Broker가 메시지를 중계한다.

따라서

**센서 → 인터넷 → 서버/클라우드**

형태의 IoT 시스템에 매우 적합하다.

---

### DDS

    Sensor Node ◀──────▶ AI Node
          ▲                 │
          │                 ▼
          └────────▶ Control Node

각 시스템이 서로 데이터를 발견하고 교환하는 분산 구조를 만들 수 있다.

따라서

**센서 ↔ 제어기 ↔ 컴퓨터 ↔ 로봇**

처럼 실시간 데이터 교환이 중요한 로봇 및 산업용 분산 시스템에 적합하다.

---

# 전체 요약

| 개념 | 핵심 내용 |
|---|---|
| Middleware | Application과 OS/Network 사이에서 통신 등의 공통 기능을 제공하는 소프트웨어 계층 |
| Distributed Computing | 여러 독립적인 컴퓨터가 네트워크를 통해 하나의 시스템처럼 협력하는 방식 |
| Network Communication | TCP/IP, UDP, Ethernet, Wi-Fi 등을 이용하여 장치 간 데이터를 전달하는 기술 |
| RTPS | DDS 시스템 간 네트워크 상호운용을 위한 Publish/Subscribe Wire Protocol |
| DDS Dynamic Discovery | 중앙 Master 없이 Participant와 Endpoint를 자동 검색하는 기능 |
| SPDP | DDS Participant를 발견하기 위한 Discovery 방식 |
| SEDP | DataWriter/DataReader 등의 Endpoint 정보를 발견하기 위한 Discovery 방식 |
| ROS1 | ROS Master 기반 Discovery + TCPROS 등의 통신 |
| ROS2 | RMW 기반 구조이며 DDS/RTPS 등을 이용한 분산 통신 가능 |
| DDS 도입 이유 | Discovery, QoS, 실시간성, 분산 시스템, 산업 표준 활용 |
| MQTT | Broker를 중심으로 하는 경량 Publish/Subscribe 프로토콜 |
| DDS | Brokerless 분산형 Data-Centric Publish/Subscribe Middleware |

# 핵심 관계

    ROS2
      │
      ▼
     RMW
      │
      ▼
     DDS                  MQTT Application
      │                         │
      ▼                         ▼
  DDSI-RTPS                 MQTT Protocol
      │                         │
      ▼                         ▼
   UDP/IP 등                    TCP
      │                         │
      ▼                         ▼
   Network                   Network

따라서 DDS와 RTPS를 같은 기술로 보는 것은 정확하지 않다.

- DDS = 데이터 중심 Publish/Subscribe 미들웨어 표준
- DDSI-RTPS = DDS 구현체들이 네트워크에서 통신하기 위한 상호운용 프로토콜
- ROS2 = RMW를 통해 DDS를 포함한 여러 Middleware를 사용할 수 있는 로봇 소프트웨어 플랫폼
- MQTT = Broker를 중심으로 동작하는 경량 Publish/Subscribe 메시징 프로토콜
