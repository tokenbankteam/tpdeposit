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
cd build
cleos -u 'http://openapi.eos.ren' set contract resource.tp ./tpdeposit -p resource.tp
```


# tpdeposit测试
## 授权
```
cleos -u 'http://openapi.eos.ren' set account permission resource.tp active '{"threshold": 1,"keys": [{"key": "EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8", "weight": 1}],"accounts": [{"permission":{"actor":"resource.tp","permission":"eosio.code"},"weight":1}]}' owner -p resource.tp@owner
```
## 添加套餐
```
cleos -u 'http://openapi.eos.ren' push action resource.tp addunit '["500000", "75000"]' -p resource.tp
cleos -u 'http://openapi.eos.ren' push action resource.tp addunit '["1000000", "15000"]' -p resource.tp
//修改套餐
cleos -u 'http://openapi.eos.ren' push action resource.tp updateunit '["188000000", "16000"]' -p resource.tp
//删除套餐
cleos -u 'http://openapi.eos.ren' push action resource.tp deleteunit '["188000000"]' -p resource.tp

```
## 更新奖励
```
cleos -u 'http://openapi.eos.ren' push action resource.tp addreward '["chendachenda", "10"]' -p resource.tp
cleos -u 'http://openapi.eos.ren' push action resource.tp updatereward '["chendachenda", "15"]' -p resource.tp
cleos -u 'http://openapi.eos.ren' push action resource.tp deletereward '["itokenpocket"]' -p resource.tp
```
## 查询套餐
```
cleos -u 'http://openapi.eos.ren' get table resource.tp resource.tp rate
cleos -u 'http://openapi.eos.ren' get table resource.tp resource.tp tpunit

## 查询当前ltokenpocket帐号的次数
cleos -u 'http://openapi.eos.ren' get table resource.tp resource.tp reward -L itokenpocket -l 1

```
## 转账购买
```
cleos -u 'http://openapi.eos.ren' transfer ptokenpocket resource.tp '0.1000 EOS' ''

//1.0000代表使用10000的套餐， 这个换算关系
cleos -u 'http://openapi.eos.ren' push action eosiotptoken transfer '["itokenpocket", "resource.tp", "1000.0000 TPT"]' -p resource.tp
```

###　测试环境
```
cleos -u 'https://kylin.eos.dfuse.io' set contract tptpresource ./tpdeposit -p tptpresource
cleos -u 'https://kylin.eos.dfuse.io' set account permission tptpresource active '{"threshold": 1,"keys": [{"key": "EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8", "weight": 1}],"accounts": [{"permission":{"actor":"tptpresource","permission":"eosio.code"},"weight":1}]}' owner -p tptpresource@owner
cleos -u 'https://kylin.eos.dfuse.io' push action tptpresource addrate '["1", "eosio.token", "0.1200 EOS", "15000"]' -p tptpresource
cleos -u 'https://kylin.eos.dfuse.io' push action tptpresource addrate '["2", "eosio.token", "0.24000 EOS", "30000"]' -p tptpresource
cleos -u 'https://kylin.eos.dfuse.io' push action tptpresource addrate '["3", "eosiotptoke1", "200.0000 TPT", "30000"]' -p tptpresource
cleos -u 'https://kylin.eos.dfuse.io' push action tptpresource addrate '["4", "eosiotptoke1", "100.0000 TPT", "15000"]' -p tptpresource

cleos -u 'https://kylin.eos.dfuse.io' push action tptpresource updaterate '["2", "eosio.token", "1.0000 EOS", "30000"]' -p tptpresource
cleos -u 'https://kylin.eos.dfuse.io' push action tptpresource updaterate '["1", "eosio.token", "0.5000 EOS", "15000"]' -p tptpresource
cleos -u 'https://kylin.eos.dfuse.io' push action tptpresource updatelimit '["30000"]' -p tptpresource
cleos -u 'https://kylin.eos.dfuse.io' push action tptpresource deletereward '["itokenpocket"]' -p tptpresource

cleos -u 'https://kylin.eos.dfuse.io' get table resource.tp resource.tp rate
cleos -u 'https://kylin.eos.dfuse.io' get table resource.tp resource.tp reward

//memo格式， a,b,c,d
//a是能兑换的网络费数量, b是兑换哪个套餐, c是推荐类型，d是推荐帐号
cleos -u 'https://kylin.eos.dfuse.io' push action eosiotptoke1 transfer '["eosiotptoke1", "tptpresource", "200.0000 TPT", "30000,3"]' -p eosiotptoke1
cleos -u 'https://kylin.eos.dfuse.io' push action eosio.token transfer '["ltokenpocket", "tptpresource", "0.5000 EOS", ""]' -p eosiotptoke1

//memo的格式 amount,id,refer,target
//amount是购买多少
//id是购买那个套餐
//refer表示推荐奖励,可以为空或者-
//target表示给那个帐号买，　如果自己买可以为空或者-
cleos -u 'https://kylin.eos.dfuse.io' push action eosio.token transfer '["ltokenpocket", "tptpresource", "0.5000 EOS", "15000,1,itokenpocket,eosiotptoke1"]' -p ltokenpocket

cleos -u 'https://kylin.eos.dfuse.io' get table tptpresource itokenpocket refbalances

cleos -u 'https://kylin.eos.dfuse.io' push action tptpresource claim '["ltokenpocket"]' -p ltokenpocket

```

#### 线上环境
```
cleos -u 'http://openapi.eos.ren' push action resource.tp addrate '["1", "eosio.token", "0.1200 EOS", "15000"]' -p resource.tp
cleos -u 'http://openapi.eos.ren' push action resource.tp addrate '["2", "eosio.token", "0.2400 EOS", "30000"]' -p resource.tp
cleos -u 'http://openapi.eos.ren' push action resource.tp addrate '["3", "eosiotptoke1", "200.0000 TPT", "30000"]' -p resource.tp
cleos -u 'http://openapi.eos.ren' push action resource.tp addrate '["4", "eosiotptoke1", "100.0000 TPT", "15000"]' -p resource.tp

cleos -u 'http://openapi.eos.ren' push action resource.tp updaterate '["2", "eosio.token", "0.2400 EOS", "30000"]' -p resource.tp
cleos -u 'http://openapi.eos.ren' push action resource.tp updaterate '["3", "eosiotptoken", "100.0000 TPT", "15000"]' -p resource.tp
cleos -u 'http://openapi.eos.ren' push action resource.tp updaterate '["4", "eosiotptoken", "200.0000 TPT", "30000"]' -p resource.tp

```
