#include "AI/TutBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

void UTutBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Check Distance Between AI Pawn and target actor
    UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
    if (ensure(BlackBoardComp))
    {
        AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));
        if (TargetActor)
        {
            AAIController* MyController = OwnerComp.GetAIOwner();
            if (ensure(MyController))
            {
                APawn* AIPawn = MyController->GetPawn();
                if (ensure(AIPawn))
                {
                    float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());
                    bool bWithinRange = DistanceTo < 2000.f;

                    bool bHasLos = false;

                    if (bWithinRange)
                    {
                        bHasLos = MyController->LineOfSightTo(TargetActor);
                    }

                    BlackBoardComp->SetValueAsBool(AttackRangedKey.SelectedKeyName, (bWithinRange && bHasLos));
                }
            }
        }
    }
}
