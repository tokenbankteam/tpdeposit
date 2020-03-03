# tpdeposit编译部署

## 依赖环境

1. eosio.cdt --- branch: release/1.5.x 或以上
2. eosio.contract --- tag:  v1.5.2 或以上

## 编译

#### 1. 将tpdeposit目录放入eosio.contracts内。
#### 2. 编辑文件 eosio.contracts/CMakeLists.txt:

```
add_subdirectory(tpdeposit)
```
#### 3. 运行eosio.contracts/build.sh完成编译
 ```
 ./build.sh
 ```
 
 ## 部署
 
```
//创建帐号
cleos -u 'https://kylin.eos.dfuse.io' system newaccount itokenpocket tpdeposit111 EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8 --buy-ram '10.0000 EOS' --stake-net '5.0000 EOS' --stake-cpu '20.0000 EOS'

cd build
cleos -u 'https://kylin.eos.dfuse.io' set contract tpdeposit111 ./tpdeposit -p tpdeposit111
```

# tpdeposit测试
## 授权
```
cleos -u 'https://kylin.eos.dfuse.io' set account permission tpdeposit111 active '{"threshold": 1,"keys": [{"key": "EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8", "weight": 1}],"accounts": [{"permission":{"actor":"tpdeposit111","permission":"eosio.code"},"weight":1}]}' owner -p tpdeposit111@owner
```
## 删除
```
cleos -u 'https://kylin.eos.dfuse.io' push action tpdeposit111 deldeposit '["21211"]' -p tpdeposit111
```
## 查询套餐
```
cleos -u 'https://kylin.eos.dfuse.io' get table tpdeposit111 tpdeposit111 deposit
```
## 充值
```
cleos -u 'https://kylin.eos.dfuse.io' push action eosio.token transfer '["itokenpocket", "tpdeposit111", "1.0000 EOS", "121212"]' -p itokenpocket
```