#pragma once
#include <iostream>

/**
 * @brief C++11 线程安全饿汉单例模式实现
 *
 * 饿汉式单例在程序启动时（main函数之前）立即初始化实例，
 * 利用静态成员变量的线程安全初始化特性，无需运行时同步。
 * 适用于初始化简单、必定使用的全局对象。
 */
class SingletonEager {
public:
  /**
   * @brief 删除拷贝构造函数
   *
   * 单例模式的核心原则是禁止拷贝构造，
   * 避免通过拷贝创建新实例破坏单例特性。
   */
  SingletonEager(const SingletonEager &) = delete;

  /**
   * @brief 删除拷贝赋值运算符
   *
   * 禁止通过赋值操作复制单例实例，
   * 确保全局唯一性。
   */
  SingletonEager &operator=(const SingletonEager &) = delete;

  /**
   * @brief 获取单例实例的全局访问点
   *
   * @return SingletonEager& 返回单例的引用（避免指针误删风险）
   *
   * 直接返回类加载时已初始化的静态实例，
   * 无运行时检查开销，性能最优。
   */
  static SingletonEager &GetInstance() { return instance_; }

  /**
   * @brief 示例成员函数
   *
   * 展示单例的功能接口。
   */
  void Print() { std::cout << "Hello world,I`m eager." << std::endl; }

private:
  /**
   * @brief 私有化默认构造函数
   *
   * 防止外部通过new或直接构造创建实例，
   * 确保只有通过GetInstance()获取单例。
   */
  SingletonEager() = default;

  /**
   * @brief 私有化析构函数
   *
   * 明确生命周期由程序控制，
   * 防止外部意外删除实例。
   */
  ~SingletonEager() = default;

  /**
   * @brief 静态成员变量（饿汉式核心）
   *
   * 1. 类加载时（程序启动阶段）立即初始化
   * 2. C++标准保证静态变量的线程安全初始化
   * 3. 存储在静态存储区，生命周期与程序一致
   */
  static SingletonEager instance_;
};

// 关键初始化（必须在类外定义）
/**
 * @brief 静态成员变量的定义式初始化
 *
 * 这是饿汉式的核心实现点：
 * 1. 必须在.cpp文件中明确定义（否则链接错误）
 * 2. 初始化时机早于main()函数执行
 * 3. 线程安全由C++标准保证（类似static局部变量）
 */
SingletonEager SingletonEager::instance_;