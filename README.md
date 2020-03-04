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
cleos -u 'http://openapi.eos.ren' system newaccount tp deposit.tp EOS76fVbNauubdaxkM4Ckm9PMkZNywetj6BwPvKdv8mMWAgP6bDKC EOS76fVbNauubdaxkM4Ckm9PMkZNywetj6BwPvKdv8mMWAgP6bDKC --buy-ram '0.1000 EOS' --stake-net '0.0010 EOS' --stake-cpu '0.0010 EOS'
cleos -u 'http://openapi.eos.ren' system buyram itokenpocket deposit.tp '5.0000 EOS'

cd build
cleos -u 'http://openapi.eos.ren' set contract deposit.tp ./tpdeposit -p deposit.tp
```

# tpdeposit测试
## 授权
```
cleos -u 'http://openapi.eos.ren' set account permission deposit.tp active '{"threshold": 1,"keys": [{"key": "EOS76fVbNauubdaxkM4Ckm9PMkZNywetj6BwPvKdv8mMWAgP6bDKC", "weight": 1}],"accounts": [{"permission":{"actor":"deposit.tp","permission":"eosio.code"},"weight":1}]}' owner -p deposit.tp@owner
```
## 删除
```
cleos -u 'http://openapi.eos.ren' push action deposit.tp deldeposit '["21211"]' -p deposit.tp
```
## 查询套餐
```
cleos -u 'http://openapi.eos.ren' get table deposit.tp deposit.tp deposit
```
## 充值
```
cleos -u 'http://openapi.eos.ren' push action eosio.token transfer '["itokenpocket", "deposit.tp", "1.0000 EOS", "121212"]' -p deposit.tp
```