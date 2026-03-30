# MeleeCombatSystem

UE5 Blueprint 기반으로 제작한 3인칭 암살 + 근접 액션 싱글플레이 프로젝트.

전투 콤보, 패링, 암살 연출, AIPerception 기반 AI 감지, Dynamic BGM 전환 시스템 등을 구현.

## 프로젝트 개요

| 항목      | 내용              |
| --------- | ----------------- |
| 엔진      | Unreal Engine 5.1 |
| 개발 방식 | Blueprint         |
| 장르      | 3인칭 암살 + 액션 |
| 플랫폼    | PC (Windows)      |
| 개발 인원 | 1                 |

---

## 주요 시스템

### 플레이어 캐릭터

- 전투, 이동, 상태, 장비, 피격, 타겟팅을 각각 별도 컴포넌트로 분리하여 관리
- Lock-On 및 좌/우 타겟 전환을 지원하며, 전투 중 타겟 유지 흐름을 고려해 입력을 분리 처리
- 위젯 열림 여부에 따라 이동/전투 입력을 차단하는 가드 처리 포함

### 전투 시스템

- Light / Heavy / Charge Attack 지원, 키 홀드 시간 추적 기반의 차지 공격
- `Attack Save` 기반 콤보 연계 — 현재 공격 중 입력을 저장하여 다음 공격으로 이어지는 구조
- Block / Parry — 블록 시작 직후 일정 시간 내 방어 판정 시 패링으로 판정
- 공격 시 무기별 스태미나 소모량을 참조하여 차감

### 피격 / 방어 파이프라인

- Dot Product 기반 전방 피격 여부를 판정하여 방어 가능 방향을 제한
- Block 시 공격 방향, 데미지 타입, 잔여 스태미나를 함께 판단해 성공/실패를 분기
- Block 성공 시 이펙트 + 사운드 재생, 실패 시 Block Break 애니메이션 또는 데미지 적용
- 패링 성공 시 공격자에게 `Parried` 상태를 부여하여 일시적 행동 정지

### Assassination System

- 적 후방에 위치한 `AssassinateBoundary` 진입 시 주기적으로 암살 조건 판정
- 조건 충족 시 암살 마커 UI 표시, 미충족 시 마커 자동 해제
- 암살 실행 시 구조체 기반 오프셋으로 플레이어-적 위치·회전을 보정하여 애니메이션 싱크 확보
- AI 행동 정지 + 카메라 전환 후 쌍방향 암살 몽타주 재생

### AI 시스템

- `AIPerception` 기반 시각 / 청각 / 피격 3채널 감지
- 시각과 피격은 즉시 전투 전환, 청각은 게이지 누적 방식으로 점진적 경계 상승 후 임계치 도달시 전투 전환
- `Blackboard` Enum 기반으로 Behavior Tree 상태 전환 (순찰, 추적, 전투, 소음 반응)
- 전투 진입/해제 시 `Blackboard` 값과 전투 상태를 연동하여 BT 분기에 반영
- 타겟 방향 회전 보간 처리, 사망 시 랜덤 애니메이션 또는 Ragdoll 전환 후 자동 제거

### 적 유형

- **일반 적 (`BP_MobEnemy`)**: 근거리 공격, 랜덤 공격 패턴 선택
- **중장형 적 (`BP_HeavyMobEnemy`)**: 일반 적과 동일 전투 구조, 별도 스탯/애니메이션 적용
- **보스 적 (`BT_BossEnemy`)**: 중거리 + 근거리 공격 분기, 쿨다운 기반 중거리 공격, 확률 기반 희귀 공격 패턴
- 공통: 체력바 / 청각 게이지 위젯 표시, 전투 진입 시 무기 소켓 전환, 사망 시 무기 물리 드랍

### Dynamic BGM

- 평시 / 전투 / 보스 상황에 따라 BGM 자동 전환
- `Combat Enemy List`를 기준으로 전투 상태를 추적하고, 리스트가 비워지면 평시 BGM으로 복귀
- MetaSound CrossFade로 BGM 간 자연스러운 전환 처리
- 보스 전투 시 전용 BGM 우선 재생, 보스 처치 후 평시 BGM으로 복귀

---

## 구현 포인트

- 컴포넌트 기반으로 전투, 상태, 장비, 타겟팅 기능을 분리해 각 시스템의 독립적인 수정과 확장이 가능하도록 구성
- 공격/방어 판정 시 방향, 상태, 자원(스태미나)을 함께 판단하여 단순 충돌이 아닌 다양한 조건 분기 구조로 처리
- 암살 연출 시작 전 구조체 기반 오프셋으로 위치를 보정해 애니메이션 싱크 문제를 보완
- `AIPerception`의 감지 결과를 즉시 반응이 아닌 `Blackboard` Enum 기반 상태 전이 흐름으로 연결
- MetaSound CrossFade를 활용해 상황 전환 시 BGM이 끊기지 않도록 점진적 보간 처리

---

## 사용 기술

- Unreal Engine 5.1
- Blueprint
- Behavior Tree / Blackboard
- AIPerception (Sight, Hearing, Damage)
- MetaSound
- GameplayTag

---

## 확인 포인트

| 분류          | 관련 BP / 에셋                    | 내용                                                                  |
| ------------- | --------------------------------- | --------------------------------------------------------------------- |
| 플레이어      | `BP_CombatPlayerCharacter`        | 플레이어 입력과 전투/이동/락온 연동 흐름 확인                         |
| 전투          | `BP_CombatComponent`              | 공격, 방어, 패링, 암살 실행이 처리되는 전투 핵심 로직 확인            |
| 피격          | `BP_TakingDamage`                 | 데미지 수신부터 방향 판정, Block/Parry 분기까지의 파이프라인 확인     |
| AI            | `BP_AIController`, `BP_MasterAI`  | `AIPerception` 결과가 상태 전환과 전투/사망 처리로 이어지는 흐름 확인 |
| 적            | `BP_MobEnemy`, `BP_HeavyMobEnemy` | `BP_MasterAI` 상속 기반 적 변형 및 공통 초기화/사망 처리 확인         |
| Behavior Tree | `BT_MobEnemy`, `BT_BossEnemy`     | 순찰/추적/전투/소음반응 분기 구조와 보스 전용 공격 패턴 확인          |
| 오디오        | `BP_MeleeGameState`, `BGMMeta`    | 전투 상태 추적 → MetaSound CrossFade BGM 전환 흐름 확인               |
