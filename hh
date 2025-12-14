-- AlippHUB | Auto Walk Script
-- Dibuat dengan WindUI Library
-- Discord: dsc.gg/alipphub

-- Load WindUI Library
local WindUI = loadstring(game:HttpGet("https://raw.githubusercontent.com/Footagesus/WindUI/main/dist/main.lua"))()

-- Konfigurasi Hub
local CONFIG = {
    HubName = "AlippHUB",
    Subtitle = "Auto Walk",
    Discord = "dsc.gg/alipphub",
    KeySystem = true,
    ValidKeys = {"TESTKEY123", "DEMO2024", "RULLZSY2024"},
    SaveKey = true
}

-- Services
local Players = game:GetService("Players")
local RunService = game:GetService("RunService")
local UserInputService = game:GetService("UserInputService")
local TweenService = game:GetService("TweenService")

local player = Players.LocalPlayer
local character = player.Character or player.CharacterAdded:Wait()
local humanoid = character:WaitForChild("Humanoid")

-- Variabel global untuk fitur
local _G = {
    Verified = false,
    AutoWalk = false,
    AutoWalkLoop = false,
    AutoRespawn = false,
    EnableGodMode = false,
    WalkSpeed = 16,
    WalkSpeedEnabled = false,
    JumpPower = 50,
    NoClip = false,
    Fly = false,
    FlySpeed = 50,
    HideNametag = false,
    FPSBooster = false
}

-- Fungsi notifikasi
local function notify(title, message, duration)
    WindUI:Notify({
        Title = title,
        Content = message,
        Duration = duration or 3
    })
end

-- Fungsi save/load/verify key (sama seperti sebelumnya)
local function saveKey(key)
    if writefile then
        writefile("AlippHUB_Key.txt", key)
    end
end

local function loadKey()
    if isfile and readfile and isfile("AlippHUB_Key.txt") then
        return readfile("AlippHUB_Key.txt")
    end
    return nil
end

local function verifyKey(key)
    for _, validKey in pairs(CONFIG.ValidKeys) do
        if key == validKey then
            return true
        end
    end
    return false
end

-- Cek saved key
local savedKey = loadKey()
if savedKey and CONFIG.SaveKey and verifyKey(savedKey) then
    _G.Verified = true
end

-- Buat Window dulu
local Window = WindUI:CreateWindow({
    Title = CONFIG.HubName,
    Subtitle = CONFIG.Subtitle,
    Icon = "activity",
    Author = "Premium",
    Folder = "AlippHUB",
    Size = UDim2.fromOffset(600, 500),
    KeySystem = false,
    Transparent = false,
    Theme = "Dark",
    DisableGuis = {
        Info = false,
        Settings = false
    }
})

-- Tab Authentication (selalu muncul)
local TabAuth = Window:Tab({
    Title = "Authentication",
    Icon = "shield-check"
})

TabAuth:Section({Title = "Key System"})

local statusParagraph = TabAuth:Paragraph({
    Title = "Status Verifikasi",
    Content = _G.Verified and "✅ Status: Verified\n👤 User: " .. player.Name .. "\n🔑 Access Level: Premium" or "⚠️ Status: Not Verified\n❌ Please enter your key below"
})

-- Variabel untuk menyimpan semua tab selain Auth
local OtherTabs = {}

-- Fungsi untuk hide semua tab kecuali Auth
local function hideAllTabsExceptAuth()
    for _, tab in pairs(OtherTabs) do
        if tab and tab.TabButton then
            tab.TabButton.Visible = false
        end
    end
end

-- Fungsi untuk show semua tab
local function showAllTabs()
    for _, tab in pairs(OtherTabs) do
        if tab and tab.TabButton then
            tab.TabButton.Visible = true
        end
    end
end

-- Jika belum verified, sembunyikan semua tab lain
if not _G.Verified then
    hideAllTabsExceptAuth()
end

-- Input key dan verifikasi
if not _G.Verified then
    TabAuth:Paragraph({
        Title = "Information",
        Content = string.format([[
Untuk mengakses menu utama, silakan masukkan key/token yang telah Anda beli melalui Discord. Jika Anda belum memiliki key/token, Anda dapat membelinya terlebih dahulu melalui server Discord kami:

🔗 %s
]], CONFIG.Discord)
    })
    
    TabAuth:Section({Title = "Input Key"})
    
    local keyInputValue = ""
    
    TabAuth:Input({
        Title = "Enter Key",
        Description = "Input your key here",
        Placeholder = "Enter key...",
        Callback = function(value)
            keyInputValue = value
        end
    })
    
    TabAuth:Button({
        Title = "Verify Key",
        Description = "Click to verify your key",
        Callback = function()
            if keyInputValue == "" then
                notify("Error", "❌ Please enter a key first!", 2)
                return
            end
            
            if verifyKey(keyInputValue) then
                _G.Verified = true
                notify("Success", "✅ Key verified! All features unlocked.", 4)
                
                if CONFIG.SaveKey then
                    saveKey(keyInputValue)
                end
                
                -- Update status
                statusParagraph:Set({Content = "✅ Status: Verified\n👤 User: " .. player.Name .. "\n🔑 Access Level: Premium"})
                
                -- Tampilkan semua tab
                showAllTabs()
            else
                notify("Error", "❌ Invalid key! Please try again.", 3)
            end
        end
    })
    
    TabAuth:Section({Title = "Butuh Bantuan?"})
    TabAuth:Paragraph({
        Title = "Troubleshooting",
        Content = [[
Jika mengalami masalah seperti:
• Key tidak bisa di pakai
• Script error atau lainnya
• Silahkan hubungi admin @alipp_
]]
    })
end

if _G.Verified then
    TabAuth:Button({
        Title = "Copy Discord Link",
        Description = "Get key from Discord",
        Callback = function()
            setclipboard(CONFIG.Discord)
            notify("Copied", "📋 Discord link copied!", 2)
        end
    })
end

-- === SEMUA TAB LAINNYA DIBUAT SETELAH INI ===
-- Setelah dibuat, masukkan ke dalam table OtherTabs agar bisa di-hide/show

-- Tab Account
local TabAccount = Window:Tab({Title = "Account", Icon = "user"})
table.insert(OtherTabs, TabAccount)

-- Tab Credits
local TabCredits = Window:Tab({Title = "Credits", Icon = "award"})
table.insert(OtherTabs, TabCredits)

-- Tab Bypass
local TabBypass = Window:Tab({Title = "Bypass", Icon = "shield-off"})
table.insert(OtherTabs, TabBypass)

-- Tab Auto Walk
local TabAutoWalk = Window:Tab({Title = "Auto Walk", Icon = "move"})
table.insert(OtherTabs, TabAutoWalk)

-- Tab Player Menu
local TabPlayer = Window:Tab({Title = "Player Menu", Icon = "users"})
table.insert(OtherTabs, TabPlayer)

-- Tab Settings
local TabSettings = Window:Tab({Title = "Settings", Icon = "settings"})
table.insert(OtherTabs, TabSettings)

-- Tab Logout
local TabLogout = Window:Tab({Title = "Logout", Icon = "log-out"})
table.insert(OtherTabs, TabLogout)

-- === ISI DARI SETIAP TAB (sama seperti script asli, tapi dibungkus dengan if _G.Verified) ===

-- Contoh untuk TabAccount (lakukan hal yang sama untuk tab lain)
if _G.Verified then
    TabAccount:Section({Title = "Account Information"})
    TabAccount:Paragraph({
        Title = "Information Account",
        Content = string.format([[
[⭕] Display Name: %s
[⭕] Username: %s
[⭕] Role: Premium Member
[⭕] Token: ********
[⭕] VIP Member: 01 Desember 2025
[⭕] Expire: 20 Days
[⭕] Status: Active
]], player.DisplayName, player.Name)
    })
    -- ... button refresh dll
else
    TabAccount:Paragraph({Title = "Tidak Terverifikasi", Content = "❌ Anda tidak terverifikasi!"})
end

-- Lakukan hal yang sama untuk semua tab lain: TabCredits, TabBypass, TabAutoWalk, TabPlayer, TabSettings, TabLogout
-- Isi konten fitur hanya jika _G.Verified == true, jika tidak tampilkan pesan "Tidak Terverifikasi"

-- Welcome message
if _G.Verified then
    notify("Welcome", "✅ Welcome to " .. CONFIG.HubName .. "!", 3)
    showAllTabs()  -- Pastikan semua tab muncul
else
    notify("Key Required", "🔐 Please enter your key to continue", 3)
    hideAllTabsExceptAuth()
end

print("AlippHUB loaded successfully!")
print("Discord: " .. CONFIG.Discord)
print("Verified: " .. tostring(_G.Verified))