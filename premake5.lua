include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "DrowFortress"
	architecture "x64"
	startproject "DrowFortress"

	configurations
	{
		"Debug",
		"Release",
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Premake"
	include "vendor/premake"

group "Game"
	include "DrowFortress"
