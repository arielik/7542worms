#include "ContactListener.h"
#include "Bodies\Missiles\Missile2d.h"

ContactListener::ContactListener() {
}

void ContactListener::BeginContact(b2Contact* contact) {

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//This assumes every sensor fixture is fluid, and will interact
	//with every dynamic body.
	if ( fixtureA->IsSensor() && fixtureB->GetBody()->GetType() == b2_dynamicBody ){
		m_fixturePairs.insert( std::make_pair(fixtureA, fixtureB) );
		return;
	}
	if ( fixtureB->IsSensor() && fixtureA->GetBody()->GetType() == b2_dynamicBody ){
		m_fixturePairs.insert( std::make_pair(fixtureB, fixtureA) );
		return;
	}
	
	b2WorldManifold worldManifold;

	//If My body (B) is touching the floor (A) (somewhere)
	if ( ( fixtureB->GetBody()->GetType() == b2_dynamicBody && (int)fixtureB->GetUserData() != UD_MISSIL )
		&& ((int)fixtureA->GetUserData() == UD_TERRAIN || (fixtureA->GetBody()->GetType() == b2_dynamicBody && (int)fixtureA->GetUserData() !=  UD_MISSIL) )){

		//Puedo comparar Y para ver si le sumo o no, basado en que si soy el de abajo no puedo saltar
		/* Si hago contacto con otro worm solo sumo si yo estoy arriba de el */ 
		if ( (int)fixtureA->GetUserData() == UD_WORMS ){
			float yB = static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getPosition().second;
			float yA = static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getPosition().second;
			if ( yB > yA ){
				static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->addGrounded();
				contact->GetWorldManifold(&worldManifold);
				static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->setNormalForce(worldManifold.normal.x,worldManifold.normal.y);
				return;
			}
		}

		static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->addGrounded();
		contact->GetWorldManifold(&worldManifold);
		static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->setNormalForce(worldManifold.normal.x,worldManifold.normal.y);
		return;
	}
	if ( ( fixtureA->GetBody()->GetType() == b2_dynamicBody && (int)fixtureA->GetUserData() != UD_MISSIL )
		&& ( (int)fixtureB->GetUserData() == UD_TERRAIN  || (fixtureB->GetBody()->GetType() == b2_dynamicBody && (int)fixtureB->GetUserData() != UD_MISSIL  )) ){
		
				/* Si hago contacto con otro worm solo sumo si yo estoy arriba de el */ 
		if ( (int)fixtureB->GetUserData() == UD_WORMS ){
			float yB = static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getPosition().second;
			float yA = static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getPosition().second;
			if ( yA > yB ){
				static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->addGrounded();
				contact->GetWorldManifold(&worldManifold);
				static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->setNormalForce(worldManifold.normal.x,worldManifold.normal.y);
				return;
			}
		}

			
		static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->addGrounded();
		contact->GetWorldManifold(&worldManifold);
		static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->setNormalForce(worldManifold.normal.x,worldManifold.normal.y);
		return;
	}

	// Contacto de misiles

/* +OVEJA y terreno: Logica de normales para el movimiento de la oveja */
	if ( (int)fixtureB->GetUserData() ==  UD_MISSIL && (int)fixtureA->GetUserData() == UD_TERRAIN){
		
		if (static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getWeaponId() == SHEEP){
			contact->GetWorldManifold(&worldManifold);
			static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->addGrounded();
			static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->setNormalForce(worldManifold.normal.x,worldManifold.normal.y);
			return;
		}

	}
	if ( (int)fixtureA->GetUserData() ==  UD_MISSIL && (int)fixtureB->GetUserData() == UD_TERRAIN){
		if (static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getWeaponId() == SHEEP){
			contact->GetWorldManifold(&worldManifold);
			static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->addGrounded();
			static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->setNormalForce(worldManifold.normal.x,worldManifold.normal.y);
			return;
		}

	}


	if ( (int)fixtureB->GetUserData() ==  UD_MISSIL && ((int)fixtureA->GetUserData() == UD_TERRAIN || fixtureA->GetBody()->GetType() == b2_dynamicBody)){
		// Si no explota por tiempo (mejor preguntar por hasDelayedExplosion )
		if (static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getWeaponId() != GRENADE && 
			static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getWeaponId() != HOLY &&
			static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getWeaponId() != DYNAMITE &&
			static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getWeaponId() != SHEEP &&
			static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getWeaponId() != BANANA &&
			static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getWeaponId() != BANANITA ){
			
				/* Misiles que colisionan: Bazooka, Burro */
				static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->setExploded(true);
				//printf("\nMISIL COLISIONO1");
				static_cast<Missile2d*>(static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->myBody)->explode();
		}

		// OVEJA y WORM
		if (static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getWeaponId() == SHEEP ){
			//Detengo la Oveja
			fixtureB->GetBody()->SetLinearVelocity( b2Vec2(0,0) );
			//Detengo el Worm
			fixtureA->GetBody()->SetLinearVelocity( b2Vec2(0,0) );
		}


		return;
	}
	if ( fixtureA->GetUserData() == (void*)UD_MISSIL && ( (int)fixtureB->GetUserData() == UD_TERRAIN  || fixtureB->GetBody()->GetType() == b2_dynamicBody) ){
		if ( static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getWeaponId() != GRENADE &&
			 static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getWeaponId() != HOLY &&
			 static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getWeaponId() != DYNAMITE &&
			 static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getWeaponId() != SHEEP &&
			 static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getWeaponId() != BANANA &&
			 static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getWeaponId() != BANANITA ){
			
				 /* Misiles que colisionan: Bazooka, Burro */
				 static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->setExploded(true);
				 //printf("\nMISIL COLISIONO2");
				 static_cast<Missile2d*>(static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->myBody)->explode();
		}

		// OVEJA y WORM
		if (static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getWeaponId() == SHEEP ){
			//Detengo la Oveja
			fixtureA->GetBody()->SetLinearVelocity( b2Vec2(0,0) );
			//Detengo el Worm
			fixtureB->GetBody()->SetLinearVelocity( b2Vec2(0,0) );
		}


		return;
	}

	


}


void ContactListener::EndContact(b2Contact* contact) {

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//This check should be the same as for BeginContact, but here
	//we remove the fixture pair
	if ( fixtureA->IsSensor() &&
		fixtureB->GetBody()->GetType() == b2_dynamicBody ){
		m_fixturePairs.erase( std::make_pair(fixtureA, fixtureB) );
		return;
	}
	else if ( fixtureB->IsSensor() &&
			fixtureA->GetBody()->GetType() == b2_dynamicBody ){
		m_fixturePairs.erase( std::make_pair(fixtureB, fixtureA) );
		return;
	}

	//If My body (B) is touching the floor (A) (somewhere)
	if ( (fixtureB->GetBody()->GetType() == b2_dynamicBody &&  (int)fixtureB->GetUserData() != UD_MISSIL)
		&& ((int)fixtureA->GetUserData() == UD_TERRAIN || ( fixtureA->GetBody()->GetType() == b2_dynamicBody && (int)fixtureA->GetUserData() != UD_MISSIL ))){

					/* Si hago contacto con otro worm solo sumo si yo estoy arriba de el */ 
		if ( (int)fixtureA->GetUserData() == UD_WORMS ){
			float yB = static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getPosition().second;
			float yA = static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getPosition().second;
			if ( yB > yA ){
				static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->reduceGrounded();
				return;
			}
		}

		static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->reduceGrounded();
		return;
	}
	if ( (fixtureA->GetBody()->GetType() == b2_dynamicBody &&  (int)fixtureA->GetUserData() != UD_MISSIL )
		&& ((int)fixtureB->GetUserData() == UD_TERRAIN || ( fixtureB->GetBody()->GetType() == b2_dynamicBody && (int)fixtureB->GetUserData() != UD_MISSIL) )){

		if ( (int)fixtureB->GetUserData() == UD_WORMS ){
			float yB = static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getPosition().second;
			float yA = static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getPosition().second;
			if ( yA > yB ){
				static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->reduceGrounded();
				return;
			}
		}


		static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->reduceGrounded();


		return;
	}


/* +OVEJA: Logica de normales para el movimiento de la oveja */
	b2WorldManifold worldManifold;
	if ( (int)fixtureB->GetUserData() ==  UD_MISSIL && (int)fixtureA->GetUserData() == UD_TERRAIN){
		
		if (static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getWeaponId() == SHEEP){
			contact->GetWorldManifold(&worldManifold);
			static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->setNormalForce(worldManifold.normal.x,worldManifold.normal.y);
			static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->reduceGrounded();
			return;
		}

	}
	if ( (int)fixtureA->GetUserData() ==  UD_MISSIL && (int)fixtureB->GetUserData() == UD_TERRAIN){
		if (static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getWeaponId() == SHEEP){
			contact->GetWorldManifold(&worldManifold);
			static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->setNormalForce(worldManifold.normal.x,worldManifold.normal.y);
			static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->reduceGrounded();
			return;
		}

	}



}


ContactListener::~ContactListener() {
}

