# 실습과제 1

### turtlesim_node 실행
<img width="909" height="672" alt="image" src="https://github.com/user-attachments/assets/607d43db-2cad-4535-842f-8d6bf3fe7195" />

### ros2 service list
<img width="907" height="339" alt="image" src="https://github.com/user-attachments/assets/5cb39791-b331-4434-9f43-e7bcbcceda76" />

### ros2 service type

<img width="906" height="122" alt="image" src="https://github.com/user-attachments/assets/1f0d1074-2db2-42ab-8351-03895e9675a4" />

### ros2 service list -t

<img width="906" height="329" alt="image" src="https://github.com/user-attachments/assets/660a258a-481e-4efa-92c1-7c360431cbbc" />

### ros2 service find

<img width="903" height="109" alt="image" src="https://github.com/user-attachments/assets/dee267e4-eedf-480f-bbe2-aa1a2eb17fb4" />

### ros2 run turtlesim turtle_teleop_key 

<img width="509" height="526" alt="image" src="https://github.com/user-attachments/assets/83780e08-c5b1-4418-bbc6-2a6899e320b2" />


<img width="711" height="717" alt="image" src="https://github.com/user-attachments/assets/f82571aa-910f-4fe9-b247-8237acf4f190" />

### ros2 service call /kill

<img width="905" height="717" alt="image" src="https://github.com/user-attachments/assets/16bba7cd-6926-442f-86c7-442f68168dd0" />


### ros2 service call /reset

<img width="724" height="746" alt="image" src="https://github.com/user-attachments/assets/991df634-0d06-4aea-bea5-2ce243338ade" />


### ros2 service call /turtle1/set_pen

<img width="907" height="868" alt="image" src="https://github.com/user-attachments/assets/10dbbb80-bc5a-4d7f-8cf8-1953058c736b" />


### ros2 service call /spawn
<img width="1439" height="750" alt="image" src="https://github.com/user-attachments/assets/24b4d99b-fbd1-45bd-be1d-d6eac34c57df" />



# 실습과제 2

# ROS 2 Turtlesim - `/turtle1/teleport_absolute` / `/turtle1/teleport_relative`

Turtlesim에서 두 서비스는 거북이(`turtle1`)를 순간이동시키는 **Service**이다.

---

## 1. `/turtle1/teleport_absolute`

현재 위치와 관계없이 **지정한 절대 좌표로 이동**한다.

### Service Type

```text
turtlesim/srv/TeleportAbsolute
```

### Request

```text
float32 x
float32 y
float32 theta
```

### 사용 예시

```bash
ros2 service call /turtle1/teleport_absolute turtlesim/srv/TeleportAbsolute "{x: 5.0, y: 5.0, theta: 1.57}"
```

### 의미

```text
x     = 5.0
y     = 5.0
theta = 1.57 rad ≈ 90°
```

즉,

> 현재 위치가 어디든 상관없이 (5, 5) 위치로 이동하고,
> 방향을 약 90°로 설정해라.

라는 의미이다.

### 핵심

```text
Absolute = 절대 좌표 기준

현재 위치 ──────────→ (5, 5)
                         ↑
                    지정한 좌표
```

---

## 2. `/turtle1/teleport_relative`

현재 turtle의 위치와 방향을 기준으로 **상대적으로 이동**한다.

### Service Type

```text
turtlesim/srv/TeleportRelative
```

### Request

```text
float32 linear
float32 angular
```

### 사용 예시

```bash
ros2 service call /turtle1/teleport_relative turtlesim/srv/TeleportRelative "{linear: 2.0, angular: 1.57}"
```

### 의미

```text
linear  = 2.0
angular = 1.57 rad ≈ 90°
```

즉,

> 현재 위치에서 현재 바라보는 방향으로 2만큼 이동하고,
> 90° 회전해라.

라는 의미이다.

### 핵심

```text
Relative = 현재 상태 기준

현재 위치
   │
   ├── 현재 바라보는 방향으로 2 이동
   │
   └── 90° 회전
```

---

## 3. Absolute vs Relative

| 서비스 | 기준 | 입력값 | 의미 |
|---|---|---|---|
| `/turtle1/teleport_absolute` | 월드 좌표 | `x, y, theta` | 지정한 좌표로 이동 |
| `/turtle1/teleport_relative` | 현재 위치/방향 | `linear, angular` | 현재 위치에서 상대적으로 이동 |

---

## 4. 예시로 비교

현재 turtle의 위치가 다음과 같다고 가정한다.

```text
현재 위치 = (2, 3)
현재 방향 = 0°
```

### Absolute

```bash
ros2 service call /turtle1/teleport_absolute turtlesim/srv/TeleportAbsolute "{x: 8.0, y: 4.0, theta: 1.57}"
```

결과:

```text
(2, 3) ─────────→ (8, 4)
```

현재 위치와 관계없이 **(8, 4)**로 이동한다.

---

### Relative

```bash
ros2 service call /turtle1/teleport_relative turtlesim/srv/TeleportRelative "{linear: 2.0, angular: 1.57}"
```

결과:

```text
현재 위치 (2, 3)
      │
      │ 현재 바라보는 방향으로 2
      ↓
      이동 후 회전
```

즉, **현재 위치와 방향을 기준으로 이동**한다.

---

## 5. 가장 쉽게 기억하는 방법

```text
absolute = "거기로 가"

relative = "지금 여기서 저만큼 움직여"
```

---

## 6. Topic과 Service의 차이

둘 다 `/cmd_vel`처럼 계속 속도를 명령하는 **Topic**이 아니다.

```text
/cmd_vel
    ↓
Topic
    ↓
계속해서 속도 명령을 전달
```

반면,

```text
/turtle1/teleport_absolute
/turtle1/teleport_relative
    ↓
Service
    ↓
특정 순간에 이동을 요청
```

따라서 다음처럼 구분하면 된다.

```text
Topic   → 지속적으로 데이터를 주고받음
Service → 특정 작업을 요청하고 결과를 받음

absolute → 절대 좌표
relative → 현재 위치 기준 상대 이동
```

---

## 한 줄 요약

```text
/turtle1/teleport_absolute
→ x, y, theta를 이용해서 "지정한 위치"로 이동

/turtle1/teleport_relative
→ linear, angular를 이용해서 "현재 위치를 기준으로" 이동
```


# ROS 2 - 주기(Period)와 주파수(Frequency)

## 1. 주기 (Period)

**한 번 실행된 후 다음 실행까지 걸리는 시간**

- 기호: `T`
- 단위: `s`, `ms`, `μs`, `ns`

```text
1 s  = 1000 ms
1 ms = 1000 μs
1 μs = 1000 ns
```

예:

```text
T = 0.1 s = 100 ms
→ 100 ms마다 1번 실행
```

---

## 2. 주파수 (Frequency)

**1초 동안 몇 번 실행되는지**

- 기호: `f`
- 단위: `Hz`

```text
1 Hz   → 1초에 1번
10 Hz  → 1초에 10번
100 Hz → 1초에 100번
```

---

## 3. 주기와 주파수 관계

```text
f = 1 / T
T = 1 / f
```

※ `T`는 초(s) 단위로 계산

예:

```text
T = 0.1 s

f = 1 / 0.1
  = 10 Hz
```

즉,

```text
10 Hz = 100 ms 주기
100 Hz = 10 ms 주기
1000 Hz = 1 ms 주기
```

---

## 4. ROS 2에서의 의미

Timer나 Publisher에서 자주 사용한다.

```cpp
create_wall_timer(
    std::chrono::milliseconds(100),
    callback
);
```

위 코드는:

```text
100 ms 주기
= 0.1 s 주기
= 10 Hz
```

즉 **약 1초에 10번 callback 실행**이다.

---

## 5. 관련 용어

```text
Period
→ 반복되는 시간 간격

Frequency
→ 초당 반복 횟수

Jitter
→ 실제 반복 간격의 미세한 변동

Latency
→ 이벤트 발생부터 처리까지 걸리는 시간
```

### 핵심

```text
주기 ↑ → 느리게 실행
주파수 ↑ → 빠르게/자주 실행

f = 1 / T
```










