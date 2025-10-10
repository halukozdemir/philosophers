# 🍽️ Philosophers

**Dining Philosophers Problem** - 42 School projesi kapsamında geliştirilmiş, çoklu thread programlama ve senkronizasyon tekniklerini öğreten bir C projesi.

## 📖 Proje Hakkında

Bu proje, klasik "Dining Philosophers Problem" (Yemek Yiyen Filozoflar Problemi) probleminin C dilinde pthread kütüphanesi kullanılarak çözümünü içerir. Proje, 42 School'un sistem programlama dersinin bir parçasıdır ve çoklu thread programlama, mutex kullanımı, deadlock önleme gibi kritik kavramları öğretir.

### 🎯 Problem Tanımı

5 filozof yuvarlak bir masada oturuyor. Her filozofun önünde bir tabak yemek var ve her filozofun solunda ve sağında bir çatal bulunuyor. Filozoflar sadece iki çatalı birden kullanarak yemek yiyebilirler. Filozoflar sırayla:
- **Düşünür** (thinking)
- **Yemek yer** (eating) 
- **Uyur** (sleeping)

### 🔧 Çözüm Yaklaşımı

Proje, **"Masa Döndürme Algoritması"** kullanarak deadlock'u önler. Her filozof sadece sol çatalını alır, sonra sağ çatalını alır. Bu yaklaşım, tüm filozofların aynı anda sol çatalını almasını engelleyerek deadlock'u önler.

## 🏗️ Proje Yapısı

```
Philosophers/
└── philo/
    ├── philo.h          # Header dosyası - veri yapıları ve fonksiyon tanımları
    ├── main.c           # Ana program - argüman kontrolü ve başlatma
    ├── init.c           # Veri yapılarının başlatılması
    ├── routine.c        # Thread rutinleri ve yönetimi
    ├── actions.c        # Filozof eylemleri (düşünme, yeme, uyuma)
    ├── utils.c          # Yardımcı fonksiyonlar
    ├── cleanup.c        # Bellek temizleme ve kaynak yönetimi
    └── Makefile         # Derleme kuralları
```

## 🚀 Kullanım

### Derleme
```bash
make
```

### Çalıştırma
```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

### Örnek Kullanım
```bash
# 5 filozof, 800ms ölüm süresi, 200ms yeme süresi, 200ms uyuma süresi
./philo 5 800 200 200

# 4 filozof, 410ms ölüm süresi, 200ms yeme süresi, 200ms uyuma süresi, her filozof 10 kez yemek yemeli
./philo 4 410 200 200 10
```

## 📊 Parametreler

| Parametre | Açıklama | Örnek |
|-----------|----------|-------|
| `number_of_philosophers` | Filozof sayısı (1-200) | `5` |
| `time_to_die` | Ölüm süresi (milisaniye) | `800` |
| `time_to_eat` | Yeme süresi (milisaniye) | `200` |
| `time_to_sleep` | Uyuma süresi (milisaniye) | `200` |
| `number_of_times_each_philosopher_must_eat` | Her filozofun yemek yeme sayısı (opsiyonel) | `10` |

## 🔒 Thread Güvenliği

Proje aşağıdaki thread güvenliği tekniklerini kullanır:

- **Mutex Locks**: Çatal erişimi için
- **Message Mutex**: Çıktı senkronizasyonu için  
- **Last Meal Mutex**: Son yemek zamanı güncellemesi için
- **End Mutex**: Program sonlandırma kontrolü için

## 🎨 Özellikler

- ✅ **Deadlock Önleme**: Masa döndürme algoritması ile
- ✅ **Race Condition Koruması**: Mutex kullanımı ile
- ✅ **Memory Leak Koruması**: Proper cleanup ile
- ✅ **Error Handling**: Kapsamlı hata kontrolü
- ✅ **Performance Optimized**: Efficient thread yönetimi

## 🔍 Test Senaryoları

```bash
# Temel test
./philo 5 800 200 200

# Tek filozof testi
./philo 1 800 200 200

# Belirli yemek sayısı testi
./philo 4 410 200 200 10

# Edge case - çok kısa süreler
./philo 3 200 100 100
```

## 📈 Algoritma Detayları

### Masa Döndürme Algoritması
1. Her filozof sadece sol çatalını alır
2. Sol çatal alındıktan sonra sağ çatal alınır
3. Her iki çatal da alındıktan sonra yemek yenir
4. Yemek bittikten sonra çatallar bırakılır
5. Bu sıralama deadlock'u önler

### Thread Yönetimi
- Her filozof ayrı bir thread olarak çalışır
- Ana thread sürekli olarak filozofların durumunu kontrol eder
- Bir filozof ölürse tüm program sonlandırılır

## 📚 Öğrenilen Kavramlar

- **Multithreading**: pthread kütüphanesi
- **Synchronization**: Mutex ve semaphore kullanımı
- **Deadlock Prevention**: Algoritma tasarımı
- **Resource Management**: Bellek ve thread yönetimi
- **System Programming**: Sistem çağrıları ve zaman yönetimi

## 📖 Detaylı Makale

Bu projenin algoritma detayları ve çözüm yaklaşımı hakkında yazdığım kapsamlı makaleyi okuyabilirsiniz:

**[Philosophers Problemi ve Çözümü: Masa Döndürme Algoritması](https://medium.com/@0halukozdemir/philosophers-problemi-ve-%C3%A7%C3%B6z%C3%BCm%C3%BC-masa-d%C3%B6nd%C3%BCrme-algoritmas%C4%B1-04ad09222eaa)**

## 🛠️ Geliştirme Ortamı

- **Dil**: C
- **Kütüphaneler**: pthread, sys/time, unistd
- **Derleyici**: gcc
- **Flags**: -Wall -Wextra -Werror
- **Platform**: Linux/Unix

## 📝 Lisans

Bu proje 42 School eğitim programı kapsamında geliştirilmiştir.

## 👨‍💻 Geliştirici

**Haluk Özdemir**  
42 Istanbul - System Programming

---

*Bu proje, çoklu thread programlama ve senkronizasyon tekniklerini öğrenmek için tasarlanmıştır. Dining Philosophers Problem'inin klasik bir çözümünü modern C programlama teknikleri ile sunar.*
