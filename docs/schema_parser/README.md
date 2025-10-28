# Парсер schemasystem

В подмодуле `source_sdk` реализован парсинг модулей, классов и полей из schema

## Прежде чем начать
Создайте экземпляр schema_parser:
```c++
const source::schema_parser parser = source::schema_parser::create();
```

## Модули (scopes)
Чтобы перечислить все существующие модули:
```c++
for (const source::c_type_scope* scope : parser.scopes())
    std::printf("supported scope: %s\n", scope->name().c_str());
```

Чтобы получить часто используемый модуль через уже готовый enum:
```c++
const auto scope = parser.get<source::scopes::client>();
```

Чтобы получить модуль по его имени:
```c++
const auto scope = parser.get("engine2.dll");
```

## Классы
Чтобы перечислить все классы из модуля:
```c++
for (const common::remote_ptr<source::c_schema_class> schema_class : scope->classes())
    std::printf("class: %s\n", schema_class->name().c_str());
```

Чтобы получить класс по имени из модуля:
```c++
const common::remote_ptr<source::c_schema_class> schema_class = scope->get("CCitadelBaseTriggerAbility");
```

### Поля
Чтобы перечислить все поля из класса:
```c++
for (const source::c_schema_field field : schema_class->fields())
    std::printf("field %s -> 0x%lX\n", field.name().c_str(), field.offset());
```

Чтобы получить поле по имени из класса:
```c++
const source::c_schema_field field = schema_class->field("m_hAbilityToTrigger");
std::printf("name: %s\n", field.name().c_str());
std::printf("offset: 0x%lX\n", field.offset());
```
