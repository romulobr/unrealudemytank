#include "battletank.h"
#include "TankTrack.h"


void UTankTrack::setThrottle(float throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Throtle set to %f"), *GetName(), throttle);
	auto ForceApplied = GetForwardVector() * throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
