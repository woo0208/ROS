## ROS 2 주요 용어 구분

### 1. 메시지(Message)
노드 간에 주고받는 실제 데이터이다.  
예를 들어 거북이의 속도, 위치, 센서값 등이 메시지에 해당한다.

예:
- `geometry_msgs/msg/Twist`
- `turtlesim/msg/Pose`

---

### 2. 토픽(Topic)
노드들이 메시지를 지속적으로 주고받기 위한 통신 채널이다.  
Publisher가 토픽으로 메시지를 보내고 Subscriber가 해당 토픽의 메시지를 수신한다.

예:
- `/turtle1/cmd_vel`
- `/turtle1/pose`

---

### 3. 서비스(Service)
한 노드가 요청(Request)을 보내면 다른 노드가 한 번 응답(Response)하는 요청-응답 방식의 통신이다.  
지속적인 데이터 전송보다는 특정 작업을 한 번 수행할 때 사용한다.

예:
- 새로운 거북이 생성
- 거북이 삭제

---

### 4. 액션(Action)
시간이 오래 걸리는 작업을 수행할 때 사용하는 통신 방식으로, 작업 요청 후 진행 상황(Feedback)을 받을 수 있고 중간에 취소할 수도 있다.

예:
- 로봇을 특정 위치까지 이동
- 일정 시간 동안 회전

---

### 5. 인터페이스(Interface)
메시지, 서비스, 액션에서 주고받는 데이터의 구조와 자료형을 정의한 규격이다.  
ROS 2에서는 `.msg`, `.srv`, `.action` 형식으로 정의된다.

예:
- Message Interface: `geometry_msgs/msg/Twist`
- Service Interface: `turtlesim/srv/Spawn`
- Action Interface: `turtlesim/action/RotateAbsolute`

---

## 핵심 차이

- 메시지: 실제로 전달되는 데이터
- 토픽: 메시지가 지속적으로 이동하는 통신 채널
- 서비스: 요청 1회와 응답 1회로 이루어진 통신
- 액션: 오래 걸리는 작업을 수행하며 진행 상황과 취소를 지원하는 통신
- 인터페이스: 메시지·서비스·액션에서 사용할 데이터 구조를 정의한 규격



---

## 토픽 + 메시지 인터페이스 출력

<img width="683" height="246" alt="image" src="https://github.com/user-attachments/assets/edeb353f-235e-4b26-abfe-964e40437bec" />

---

## 실제 토픽 메시지 출력

### 위치 명령 메시지:
<img width="719" height="367" alt="image" src="https://github.com/user-attachments/assets/12ce8e3e-0acd-442e-8309-bb9c275b92ce" />

### 속도 명령 메시지:
<img width="791" height="539" alt="image" src="https://github.com/user-attachments/assets/540fb39f-2fb4-4548-8e5c-379773406b89" />

---

## 메시지 인터페이스 정의 출력
<img width="848" height="483" alt="image" src="https://github.com/user-attachments/assets/8ba1bccf-a234-4d76-9745-4ddd457f7504" />


