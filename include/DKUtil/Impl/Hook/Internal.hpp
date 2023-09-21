#pragma once

#include "assembly.hpp"
#include "jit.hpp"
#include "trampoline.hpp"

namespace DKUtil::Hook
{
	using namespace Assembly;

	class HookHandle
	{
	public:
		virtual ~HookHandle() = default;

		virtual void Enable() noexcept = 0;
		virtual void Disable() noexcept = 0;

		template <std::derived_from<HookHandle> derived_t>
		constexpr derived_t* As() noexcept
		{
			return dynamic_cast<derived_t*>(this);
		}

		const std::uintptr_t Address;
		const std::uintptr_t TramEntry;
		std::uintptr_t       TramPtr{ 0x0 };

	protected:
		HookHandle(const std::uintptr_t a_address, const std::uintptr_t a_tramEntry) :
			Address(a_address), TramEntry(a_tramEntry), TramPtr(a_tramEntry)
		{}
	};
}  // namespace DKUtil::Hook

#define DKU_H_INTERNAL_IMPORTS DKU_H_VERSION_MAJOR

#include "Internal/ASMPatch.hpp"
#include "Internal/CaveHook.hpp"
#include "Internal/IATHook.hpp"
#include "Internal/RelHook.hpp"
#include "Internal/VMTHook.hpp"

#undef DKU_H_INTERNAL_IMPORTS
