# SamEngine 

**SamEngine**, oyun motoru mimarisini ve OpenGL grafik programlamayı en temelden öğrenmek amacıyla başlattığım bir **hobi projesidir.** Bu proje, "Bir oyun motoru arka planda nasıl çalışır?" sorusuna cevap ararken öğrendiğim teknikleri uyguladığım bir kişisel gelişim alanıdır. Ticari bir amaç gütmeden, tamamen temiz kod yazma prensiplerini ve grafik programlama mantığını kavrama odaklı geliştirilmektedir.

## Öğrenme Hedeflerim
* OpenGL render hattı (pipeline) sürecini derinlemesine anlamak.
* C++ ile bellek yönetimi ve RAII prensiplerini uygulamak.
* Shader yönetimi ve matematiksel ışıklandırma modellerini (Phong vb.) kavramak.
* Verimli kaynak (Resource) yönetimi sistemleri kurmak.

## Şu Ana Kadar Neler Yaptım?
* **Modern Window Yapısı:** GLFW'yi kapsülleyen, statik callback desteği sunan ve RAII prensibine uygun modüler bir `Window` sınıfı.
* **DeltaTime Sistemi:** Kare hızından bağımsız (frame-rate independent) akıcı hareketler için zaman yönetimi.
* **Akıllı Shader Sistemi:** Shader'ları kolayca yükleyen, uniform lokasyonlarını önbelleğe alan (Caching) ve detaylı loglama yapan profesyonel bir yapı.
* **Texture Manager:** Singleton desenini kullanarak dokuları `std::unordered_map` ile yöneten, mükerrer yüklemeleri önleyerek performansı artıran sistem.
* **Temel Aydınlatma:** Ambient, Diffuse ve Specular bileşenlerinden oluşan Phong ışıklandırma modeli entegrasyonu.

## Teknik Araçlar
* **Dil:** C++20
* **Grafik API:** OpenGL 3.3 (Core Profile)
* **Kütüphaneler:** GLFW, GLAD, GLM, stb_image
* **Derleme Sistemi:** CMake

## Geliştirme Süreci (WIP)
Bu proje sürekli gelişmektedir. Bir sonraki aşamalarda şunları eklemeyi planlıyorum:
- [ ] Shader ve Mesh yönetimi için Material sınıfı( json tabanlı olabilir)
- [ ] Transform Component ve Entity sistemi
- [ ] Entityler için active,deactive olarak basit sahne yönetimi (yine json tabanlı olabilir)
- [ ] `.obj` dosyalarını yükleyebilmek için Model Loader sistemi.
- [ ] Daha gelişmiş ve merkezi bir Input Manager.
- [ ] Hata ayıklama ve sahne yönetimi için ImGui entegrasyonu.
- [ ] Farklı ışık türleri (Directional, Point, Spot Light).
- [ ] Entity Component System
- [ ] Sahne Yönetimi
