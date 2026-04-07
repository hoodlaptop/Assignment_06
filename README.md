# Assignment_06 - Puzzle Platform

Unreal Engine 5.5 C++ 기반 퍼즐 플랫폼 프로젝트입니다.

---

## 구현 기능

### 필수 기능

#### Actor 클래스 2종 구현
- **MovingActor** : 왕복 이동 발판. `StartLocation` 기준으로 `MaxRange` 범위 내에서 앞뒤로 이동
- **RotatingActor** : 회전 발판. Y축 기준으로 매 프레임 회전

#### Tick 기반 동적 Transform
- 이동/회전 모두 `DeltaTime`을 곱해 프레임 독립적으로 동작
- `MovingActor::Move()`, `RotatingActor::Rotate()` 함수로 로직 분리

#### UPROPERTY 리플렉션
- `MovingSpeed`, `MaxRange`, `RotateSpeed` 등 주요 수치를 `EditAnywhere | BlueprintReadWrite`로 선언
- 에디터 Details 패널에서 액터별로 개별 조정 가능
- `Category` 계층 구조(`MovingActor|Movement`, `MovingActor|Timer` 등)로 정리

---

### 도전 기능

#### 타이머 시스템
- `FTimerHandle` + `GetTimerManager().SetTimer()`로 일정 시간 후 액터 제거
- `bShouldDisappear` bool로 사라지는 기능 활성화 여부를 에디터에서 제어
- `DisappearTime`으로 몇 초 후 사라질지 설정 가능

#### 랜덤 퍼즐 생성 (PlatformSpawner)
- `SpawnActor`로 MovingActor / RotatingActor를 런타임에 동적 스폰
- `FMath::RandRange`로 속도, 범위, 사라지는 시간을 매번 다르게 부여
- `SpawnInterval`마다 주기적으로 스폰 (타이머 반복)
- 스포너 액터의 위치를 중심으로 `SpawnRangeXY` 범위 내 랜덤 배치

---

## 트러블 슈팅

### 1. C4458 - 지역변수가 클래스 멤버를 가림
**증상**
```
error C4458: declaration of 'StartLocation' hides class member
```
**원인**
`BeginPlay()` 안에서 `FVector StartLocation = GetActorLocation()`으로 작성해 지역변수를 새로 선언함

**해결**
타입 선언 없이 `StartLocation = GetActorLocation()`으로 클래스 멤버에 직접 대입

---

### 2. 생성자에서 GetWorld() 호출 시 크래시
**증상**
에디터 실행 시 크래시 또는 Null 접근 오류

**원인**
`SetTimer()`를 생성자에서 호출했는데, 생성자 시점에는 `GetWorld()`가 `nullptr`을 반환함

**해결**
`SetTimer()` 호출을 생성자에서 `BeginPlay()`로 이동

---

### 3. 액터가 움직이지 않음
**증상**
에디터에 배치한 액터가 플레이해도 이동/회전을 하지 않음

**원인**
`bIsActive` 기본값이 `false`로 설정되어 있어 `Move()`, `Rotate()` 함수가 즉시 `return`됨

**해결**
`bIsActive` 기본값을 `true`로 변경

---

### 4. 에디터 배치 액터도 사라지는 문제
**증상**
직접 배치한 액터가 스폰된 액터처럼 일정 시간 후 사라짐

**원인**
사라지는 기능을 `bIsActive` 하나로 제어하다 보니 이동/회전 활성화와 타이머 등록 로직이 혼재됨

**해결**
`bShouldDisappear` bool을 별도로 추가해 역할 분리
- 에디터 배치 액터 → `bShouldDisappear = false` (기본값) → 타이머 미등록
- 스포너가 생성한 액터 → `SetupDisappearTimer()` 호출로 타이머 강제 등록

---

### 5. 스폰된 액터에 타이머가 적용되지 않음
**증상**
`SpawnActor` 후 `bShouldDisappear = true`로 설정해도 타이머가 동작하지 않음

**원인**
`SpawnActor`는 내부적으로 `BeginPlay()`를 즉시 호출하므로, 반환 이후에 프로퍼티를 설정하면 `BeginPlay()`의 타이머 등록 조건을 이미 지나친 상태

**해결**
`SetupDisappearTimer(float Time)` 함수를 별도로 만들어 스폰 후 직접 호출

---

### 6. 스폰 위치가 월드 원점(0, 0, 0) 기준으로 생성됨
**증상**
스포너 액터를 다른 위치에 놓아도 항상 월드 중앙 근처에 스폰됨

**원인**
`FVector(RandX, RandY, Z)`를 절대 좌표로 사용

**해결**
`GetActorLocation() + FVector(RandX, RandY, 0.0f)`로 스포너 위치 기준 오프셋으로 변경

---

### 7. MovingActor 타이머 설정 시 잘못된 대상에 대입
**증상**
MovingActor의 `ToggleInterval`이 항상 같은 값으로 설정됨

**원인**
```cpp
// Moving 스폰 후 Rotating 변수에 실수로 대입
Rotating->ToggleInterval = FMath::RandRange(1.0f, 5.0f);
```

**해결**
```cpp
Moving->ToggleInterval = FMath::RandRange(1.0f, 5.0f);
```
