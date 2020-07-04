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
cleos -u 'http://openapi.eos.ren' system newaccount tp deposit1.tp EOS76fVbNauubdaxkM4Ckm9PMkZNywetj6BwPvKdv8mMWAgP6bDKC EOS76fVbNauubdaxkM4Ckm9PMkZNywetj6BwPvKdv8mMWAgP6bDKC --buy-ram '0.1000 EOS' --stake-net '0.0010 EOS' --stake-cpu '0.0010 EOS'
cleos -u 'http://openapi.eos.ren' system buyram itokenpocket deposit1.tp '5.0000 EOS' -p itokenpocket@active

cd build
cleos -u 'http://openapi.eos.ren' set contract deposit1.tp ./tpdeposit -p deposit1.tp
```

# tpdeposit测试
## 授权
```
cleos -u 'http://openapi.eos.ren' set account permission deposit1.tp active '{"threshold": 1,"keys": [{"key": "EOS76fVbNauubdaxkM4Ckm9PMkZNywetj6BwPvKdv8mMWAgP6bDKC", "weight": 1}],"accounts": [{"permission":{"actor":"deposit1.tp","permission":"eosio.code"},"weight":1}]}' owner -p deposit1.tp@owner
```
## 删除
```
cleos -u 'http://openapi.eos.ren' push action deposit1.tp deldeposit '["0"]' -p deposit1.tp
```
## 查询套餐
```
cleos -u 'http://openapi.eos.ren' get table deposit1.tp deposit1.tp deposit
```
## 充值
```
cleos -u 'http://openapi.eos.ren' push action eosio.token transfer '["itokenpocket", "deposit1.tp", "1.0000 EOS", "121212"]' -p deposit1.tp
cleos -u 'http://openapi.eos.ren' push action eosio.token transfer '["itokenpocket", "deposit1.tp", "1.0000 EOS", "121212:wallet"]' -p deposit1.tp
```