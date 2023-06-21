// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacterController.h"

#include "SAttributeComp.h"
#include "SInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacterController::ASCharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);

	SpringArmComp->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<USAttributeComp>("AttributeComp");

	AbilitySystemComp = CreateDefaultSubobject<USAbilitySystemComponent>("AbilitySystemComp");
}

// Called when the game starts or when spawned
void ASCharacterController::BeginPlay()
{
	Super::BeginPlay();

	check(AbilitySystemComp);

	AbilitySystemComp->InitAbilityActorInfo(this,this);
		
	if(GameplayAbilities.Num())
	{
		for(int i = 0;i < GameplayAbilities.Num();i++)
		{
			if(GameplayAbilities[i] == nullptr) continue;
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(GameplayAbilities[i].GetDefaultObject(),1,0));
		}
	}
}

void ASCharacterController::OnHealthChanged(AActor* InstigatorActor, USAttributeComp* Owningcomp, float NewHealth,
	float Delta)
{
	if(NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController * pc = Cast<APlayerController>(GetController());
		DisableInput(pc);
	}
}

void ASCharacterController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChHangDelegated.AddDynamic(this,&ASCharacterController::OnHealthChanged);
}

void ASCharacterController::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(),value);
}

void ASCharacterController::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector,value);
}

void ASCharacterController::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,this,&ASCharacterController::PrimaryAttack_TimeElapsed,0.2f);

	AttributeComp->ApplyChangeMagic(10.0f);

	//ActionComp->StartActionByName(this,"PrimaryAttack");
}

void ASCharacterController::PrimaryInteract()
{
	if(InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ASCharacterController::PrimaryAttack_TimeElapsed()
{
	if(ensure(ProjectileClass))
	{
		FVector HandleLoc = GetMesh()->GetSocketLocation("weaponProjectileSpawn");
		FTransform SpawnTS = FTransform(GetControlRotation(),HandleLoc);
	
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = this;
		GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTS,SpawnParameters);
	}
}

// Called every frame
void ASCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ASCharacterController::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}

// Called to bind functionality to input
void ASCharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward",this,&ASCharacterController::MoveForward);
	InputComponent->BindAxis("MoveRight",this,&ASCharacterController::MoveRight);
	
	InputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	InputComponent->BindAxis("Lookup",this,&APawn::AddControllerPitchInput);

	InputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&ASCharacterController::PrimaryAttack);
	InputComponent->BindAction("PrimaryInteract",IE_Pressed,this,&ASCharacterController::PrimaryInteract);
	InputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	
}

UAbilitySystemComponent* ASCharacterController::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

