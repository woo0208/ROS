# ROS 2 Jazzy 기본 환경 및 동작 확인

Ubuntu 24.04 환경에서 ROS 2 Jazzy를 설치하고, 기본 명령어와 Publisher / Subscriber 통신을 확인하였다.

## 실습 환경

| 항목         | 내용                      |
| ---------- | ----------------------- |
| OS         | Ubuntu 24.04 LTS (WSL2) |
| ROS 2      | Jazzy                   |
| Build Tool | colcon                  |

---

## 1. ROS 2 명령어 확인

```bash
ros2 --help
```

ROS 2에서 사용할 수 있는 기본 명령어를 확인하였다.

<img width="1269" height="635" alt="ros2 help" src="https://github.com/user-attachments/assets/80b5bacd-bca6-497f-b8e0-e2bbd492683e" />

---

## 2. colcon 명령어 확인

```bash
colcon --help
```

ROS 2 Workspace 및 Package를 빌드할 때 사용하는 `colcon` 명령어의 옵션을 확인하였다.

<img width="1253" height="1043" alt="colcon help" src="https://github.com/user-attachments/assets/47e2c28a-8d61-440c-b22e-1008489349bb" />

---

## 3. Talker / Listener 통신 확인

### Talker 실행

```bash
ros2 run demo_nodes_cpp talker
```

### Listener 실행

```bash
ros2 run demo_nodes_py listener
```

Talker 노드가 `/chatter` Topic으로 메시지를 Publish하고, Listener 노드가 해당 메시지를 Subscribe하는 것을 확인하였다.

<img width="1740" height="448" alt="talker listener" src="https://github.com/user-attachments/assets/124a1631-800e-48df-b3de-d34ccae98828" />

---

## 4. 추가 실습 결과

11페이지 실습 내용을 실행하고 결과를 확인하였다.

<img width="961" height="809" alt="ROS2 practice result" src="https://github.com/user-attachments/assets/6bfa35ba-764c-4a08-82c4-d5084d490294" />

