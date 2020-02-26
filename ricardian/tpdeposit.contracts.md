<h1 class="contract"> transfer </h1>

Stub for transfer action's ricardian contractrameters
Input parameters:

* `from` (from account to do transfer action)
* `to` (to account to do transfer action)
* `quantity` (asset transfer action)
* `memo` (memo transfer action)

Implied parameters: 

* `account_name` (name of the party invoking and signing the contract)

### Intent
INTENT. The intention of the action is to do swap reward.

### Term
TERM. This Contract expires at the conclusion of code execution.

<h1 class="contract"> addreward </h1>

Stub for addreward action's ricardian contractrameters
Input parameters:

* `ru` (memo transfer action)
* `unit` (memo transfer action)

Implied parameters: 

* `token_contract` (name of the party invoking and signing the contract)

### Intent
INTENT. The intention of the action is to add reward.

### Term
TERM. This Contract expires at the conclusion of code execution.

<h1 class="contract"> updatereward </h1>

Stub for updatereward action's ricardian contractrameters
Input parameters:

* `id` (id to update)
* `token_contract` (contract name to update to do action)
* `symbol` (symbol info to do action)
* `rc` (reward count)
* `ru` (reward unit)
* `unit` (unit)

Implied parameters: 

* `id` (name of the party invoking and signing the contract)
* `token_contract` (name of the party invoking and signing the contract)

### Intent
INTENT. The intention of the action is to update reward.

### Term
TERM. This Contract expires at the conclusion of code execution.


<h1 class="contract"> deletereward </h1>

Stub for updatereward action's ricardian contractrameters
Input parameters:

* `id` (id to update)

Implied parameters: 

* `id` (name of the party invoking and signing the contract)

### Intent
INTENT. The intention of the action is to delete reward.

### Term
TERM. This Contract expires at the conclusion of code execution.
