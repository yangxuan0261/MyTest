#pragma once
#include "Engine/DataAsset.h"
#include "ItemInfoDatabase.generated.h"

class AMyActor;

USTRUCT()
struct FAssetInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "DATA")
		int32 MeshID;

	UPROPERTY(EditAnywhere, Category = "DATA")
		TAssetPtr<USkeletalMesh> MeshResource;
	UPROPERTY(EditAnywhere, Category = "DATA")
		TAssetPtr<UTexture2D> Texture;
	UPROPERTY(EditAnywhere, Category = "DATA")
		TAssetPtr<AMyActor> MyActor;


	FAssetInfo()
	{
		MeshID = 0;
		MeshResource = FStringAssetReference("");
		Texture = FStringAssetReference("");
		MyActor = FStringAssetReference("");
	}
};

UCLASS(BlueprintType, Blueprintable)
class UItemInfoDatabase : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "UItemInfoDatabase") //Exposes the array as editable on editor
		TArray<FAssetInfo> MeshList;

public:
	UItemInfoDatabase();
};