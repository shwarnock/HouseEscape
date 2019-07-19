#include "Messenger.h"

void UMessenger::CollideWithInteractable(FMessage message)
{
	OnCollideWithInteractable.Broadcast(message);
}

void UMessenger::EndCollideWithInteractable(FMessage message)
{
	OnEndCollideWithInteractable.Broadcast(message);
}

void UMessenger::RemoveAllWidgets()
{
	OnRemoveAllWidgets.Broadcast();
}

void UMessenger::PuzzleSolved(FMessage message)
{
	OnPuzzleSolved.Broadcast(message);
}

void UMessenger::KeyPickedUp(FMessage message)
{
	OnKeyPickedUp.Broadcast(message);
}

void UMessenger::ItemPickedUp(FMessage message)
{
	OnItemPickedUp.Broadcast(message);
}

void UMessenger::AddInteractTarget(FMessage message)
{
	OnAddInteractTarget.Broadcast(message);
}

void UMessenger::RemoveInteractTarget(FMessage message)
{
	OnRemoveInteract.Broadcast(message);
}

void UMessenger::UpdateInteractUI(FMessage message)
{
	OnUpdateInteractUI.Broadcast(message);
}

void UMessenger::ToggleInventory(FMessage message)
{
	OnToggleInventory.Broadcast(message);
}

void UMessenger::InventoryItemSelected(FMessage message)
{
	OnInventoryItemSelected.Broadcast(message);
}

void UMessenger::ItemRemoved(FMessage message)
{
	OnItemRemoved.Broadcast(message);
}