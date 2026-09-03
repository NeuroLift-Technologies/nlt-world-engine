#include "Agents/NLTAgentTrait.h"
#include "Agents/NLTAgentFragments.h"
#include "MassEntityManager.h"
#include "MassEntityTemplateRegistry.h"

void UNLTAgentTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
    FNLTAgentIdentityFragment& Identity = BuildContext.AddFragment_GetRef<FNLTAgentIdentityFragment>();
    Identity.ProfileId = ProfileId;
    Identity.Role = Role;
    Identity.DisplayName = *DisplayName;

    FNLTAgentLocationFragment& Location = BuildContext.AddFragment_GetRef<FNLTAgentLocationFragment>();
    Location.Position = InitialPosition;

    BuildContext.AddFragment<FNLTAgentIntentFragment>();
    BuildContext.AddFragment<FNLTAgentCognitiveFragment>();
    BuildContext.AddFragment<FNLTAgentNeedsFragment>();
    BuildContext.AddFragment<FNLTAgentBehaviorFragment>();

    if (bCanMove)
    {
        BuildContext.AddFragment<FMassVelocityFragment>();
        BuildContext.AddFragment<FMassDesiredMovementFragment>();
        BuildContext.AddFragment<FMassForceFragment>();
        BuildContext.AddTag<FMassCodeDrivenMovementTag>();
    }
}
